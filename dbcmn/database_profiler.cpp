// File: database_profiler.cpp
// Todo: Add Doxygen comments to all functions as a profile @function, etc. 
// #include <memory>   // std::auto_ptr<T> still supported with C++ 11

// Translate -DPROD=$(prod) to string $(prod) - this requires double expansion. 
// Note: #include macro-string also permitted per ANSI C/C++ standard for 
// for parameterized includes without requiring strings on compiler command
// line.
#define _MK_STR(S) #S
#define MK_STR(S) _MK_STR(S)

#include <iostream>
#include <thread>
#include <iterator>
#include <cassert>
#include <ctime>
#include <cstring>

#include "database_profiler.hpp"

#ifndef DEFAULT_DB_TRANS_LENGTH
#if defined(MCO) || defined(mco)
    #define DEFAULT_DB_TRANS_LENGTH (1 * 1000)
#elif defined(RDM14) || defined(rdm14)
    #define DEFAULT_DB_TRANS_LENGTH (100 * 1000)
#elif defined(RDM12) || defined(rdm12)
    #define DEFAULT_DB_TRANS_LENGTH (25 * 1000)
#elif defined(SQLITE) || defined(sqlite)
    #define DEFAULT_DB_TRANS_LENGTH (50 * 1000)
#else
    #error "Database Product ID not set- build error"
#endif
#endif

// terminate called without an active exception if thread is active on create
// if not defined, then rdm exception caught - reason: std::exception which 
// doesn't make a lot of sense to me -- a std::exception is not a reason but
// this is what RDM14 tells me on a create on an already populated database.
#define READER_THREAD

////////////////////////////////////////////////////////////////////////////////
// for sqlite either reduce this with #if 0or only if PROD!=sqlite or use a
// a vector file for sqlite that limits at runtime the size of the markers and 
// the population limit as the last vector entry to less than 20M or 10M or
// 5M as sqlite takes a while. Passing a vector file is most flexible
// see help function or run program with -help option.
// 
// program [marker-seq-file] [-t trans-length] [-p popsize] [-s simcount] [-f key_file]
// Example:
// program markers.txt 1000 -t 500 -p 100000 -s 1000 -f keys.txt

////////////////////////////////////////////////////////////////////////////////

// inserts only - and into an empty or initialized database. 
// time elapsed sampling points or markers
std::vector<unsigned> default_pop_markers = 
{
    100000,     // 100,000
    1000000,    // 1M
    5000000,    // 5M
    10000000,   // 10M
    20000000    // 20M
};

// create, read(find), update, deletesy
// time elapsed sampling points or markers
std::vector<unsigned> default_update_list_markers = 
{
    50000,      // 50,000
    100000,     // 100,000
    150000,     // 150,000
    200000      // 200,000 - agreed as 2X the reasonable import update list
};


////////////////////////////////////////////////////////////////////////////////

void strip_path(std::string & fn)
{
    // strip windows or unix pathing on filenames
    fn = fn.substr(fn.find_last_of("\\/") + 1); 
}

////////////////////////////////////////////////////////////////////////////////

void help(const char * const program)
{
    assert(program != 0);
    std::cout << "\nusage: program [-pm pop-marker-seq-file] [-um update-list-marker-seq-file] [-t trans-length] [-p popsize] [-s simcount] [-f key_file]" << std::endl;
    std::cout << "example: " << program << " -pm popmarkers.txt -um update-markers.txt -t 1000 -p 500 -s 100000 -f key_file.txt" << std::endl;
    std::cout << "\nIf more use of these argc, argv options, convert to Options<T> member data ptr impl for named unary|binary opts\n";

    std::cout   << " -p population size (popsize)\n"
                << " -s simulation count (simcount)\n"
                << " -t transaction length (trans_length)\n"
                << " -f key file (key_file)\n"
                << " -pm pop markers filename (pop_markers_filename)\n"
                << " -um update list markers filename (update_list_markers_filename)\n";

    std::cout << "Note: popsize and simcount should correlate in relationship to marker-seq-file or defaults\n";
    std::cout << "\nDefaults: \n";
    unsigned n = 1;
    for (unsigned i : default_pop_markers) {
        std::cout << "\tmarker " << n++ << ": " << i << std::endl;
    }

    std::cout << "\ndefault trans length = " << DEFAULT_DB_TRANS_LENGTH << std::endl;

    const unsigned last_default_value = default_pop_markers[default_pop_markers.size() - 1];
    std::cout << "default popsize (last marker) = " << last_default_value << std::endl;
    std::cout << "default simcout (last marker) = " << last_default_value << std::endl; 

    std::cout << "\n\n -- end help -- \n\n";
}

////////////////////////////////////////////////////////////////////////////////

void validate_vector_values_ascending(const std::vector<unsigned> & vec)
{
   // values in vector must be non-zero and ascending
    unsigned m = 0;
    for (unsigned n : vec) {
        assert(n > m && "marker values must be ascending non-zero values");  
        m = n;
    }
}

////////////////////////////////////////////////////////////////////////////////

Database::Profiler::Profiler(const int argc, const char * const argv[])
        : impl_(0), skey_(0), card_reader_thread_exit_(false)
{
    // initialize options.
    set_prof_opts(argc, argv);

    // free function factory pattern, request an implementation. 
    impl_ = createProfilerImpl();
    assert(impl_ != 0);

    // I could adjust based on PROD=sqlite and reduce these numbers however
    // passing the file with the default markers override is cleaner
    // see help above. 
    impl_->stats_.requested_rec_count = opts.popsize;
    impl_->stats_.requested_sim_count = opts.simcount;
    impl_->stats_.requested_trans_grp_sz = opts.trans_length;

    // initialize consistent with requested range of num records to be created
    // bug here ... I need to create a salted key for automatic increment
    // monotonic and one for random with duplicates possible. .. 
    // hacked into it for now - hits beyond which is probably okay
    skey_ = new SaltedKey(0, impl_->stats_.requested_rec_count);

    // values in vector must be non-zero and ascending
    unsigned m = 0;
    for (unsigned n : opts.pop_markers) {
        assert(n > m && "pop markers must be ascending non-zero values");  
        m = n;
    }

    m = 0;
    for (unsigned n : opts.update_list_markers) {
        assert(n > m && "sim markers must be ascending non-zero values");  
        m = n;
    }
}

////////////////////////////////////////////////////////////////////////////////

Database::Profiler::~Profiler()
{
    delete skey_;
    release(impl_);
}

////////////////////////////////////////////////////////////////////////////////

bool Database::Profiler::is_db_empty()
{
    assert(impl_);
    const bool rc = impl_->is_db_empty(); 
    return rc; 
}

////////////////////////////////////////////////////////////////////////////////

void Database::Profiler::print_opts(void)
{
    std::cout << "pop db csv filename: " << opts.pop_csv_fn << std::endl;
    std::cout << "update list csv_filename: " << opts.impsim_csv_fn << std::endl;

    std::cout << "\npop_markers vector contents:" << std::endl;
    unsigned n = 1;
    for (unsigned i : opts.pop_markers) {
        std::cout << "\tpop_marker #" << n++ << ": " << i << std::endl;
    }

    std::cout << std::endl;

    std::cout << "\nupdate list markers vector contents:" << std::endl;
    n = 1;
    for (unsigned i : opts.update_list_markers) {
        std::cout << "\tupdate_list_marker #" << n++ << ": " << i << std::endl;
    }

    std::cout << "\ntrans length = " << opts.trans_length << std::endl;
    std::cout << "popsize      = " << opts.popsize << std::endl;
    std::cout << "simcount     = " << opts.simcount << std::endl;

    if (!opts.key_file.empty()) 
        std::cout << "Salted key filename: " << opts.key_file << std::endl;

}

////////////////////////////////////////////////////////////////////////////////

bool Database::Profiler::open_db(const unsigned number_of_threads)
{
    assert(number_of_threads != 0);

    // wrap open in terms of exception in impl_ and catch translates to false
    const bool rc = impl_->open_db(number_of_threads);
    return rc;
}

////////////////////////////////////////////////////////////////////////////////

// handle case: of m to n modulo calculations. 
// transaction grp size is greater than the number of records
// then transaction grp size is 1
// This calculation works if m >= n or m < n, where m < n => 1 
// n = 0 makes no sense - 0 transactions is not permitted. 
// m = 0 makes no sense either - 0 records ? 
void Database::Profiler::populate_db()
{
    assert(impl_);
    assert(skey_);

    // db must be empty.
    assert(impl_->is_db_empty());

    const auto m = impl_->stats_.requested_rec_count;
    auto n = impl_->stats_.requested_trans_grp_sz;
    assert(m > 0); 
    assert(n > 0);
    assert(!opts.pop_csv_fn.empty());

    std::ifstream infile;
    std::ofstream pop_csv_log(opts.pop_csv_fn, std::ios::out | std::ios::trunc);
    if (!opts.key_file.empty()) {
        infile.open(opts.key_file);
        if (!infile) {
            // options provided a key file name that does not exist
            std::cout << "key file " << opts.key_file << " not found " << std::endl;
            exit(0); // or throw std::logic_error, std::runtime_error exception
        }
    }

    // calculate number of transactions and track total to calculate 
    // record counts within each transaction including remainders
    time_t start, end;
    time(&start);         
    const unsigned trans_grps = (m + (n - 1)) / n;
    unsigned total = 0, vi = 0;
    for (unsigned int i = 0; i < trans_grps; ++i) {
        std::cout << "pop trans_grp # " << i + 1 << " of "<< trans_grps <<  std::endl;
        assert(m > total);

        if ((m - total) < n)    // last transaction group is not modulo n
            n = m - total;      // whats left is less than n, update n remainder

        impl_->tx_begin();
        for (unsigned int j = 0; j < n; ++j) {
            if (!opts.key_file.empty()) {
                std::string line;
                std::getline(infile, line);
                assert(!line.empty() && "file too small for pop rec count requested");  
                skey_->key(line.c_str());
            } else {
                skey_->key(total);
            }
            impl_->create_rec(*skey_);
            impl_->stats_.pop_rec_count  = ++total; 

            // checkpoint marker - update the csv log file with current record 
            // count and elapsed time up to this point.
            if (total == opts.pop_markers[vi]) {
                time(&end);
                time_t delta = difftime(end, start);
                pop_csv_log << MK_STR(PROD) << "," << opts.pop_markers[vi++] 
                            << "," << delta << std::endl;
            }
        }     
        impl_->tx_end();
    } // end outer for loop

    // input file is at least as big as the requested records to import
    assert(total == m && "sorted file size was too small for requested count");

    // optional flush used by McObject only - defaulted to nothing for others
    impl_->tx_sync();
}

////////////////////////////////////////////////////////////////////////////////

// Note: Using functor operator()() for Database::Profiler may look like a good
// idea and pass *this to the thread constructor however this is a bug just 
// waiting to happen (and did happen) as the thread creates a copy of the object 
// to which the functor is applied. Very deceptive bug and a idiosynchrasie of
// std::thread. The examples use std::thread with (Object()) as an argument so
// thats a clue a copy is being made and card_reader_thread_exit_ will not be
// recognized as changing state to the profiler object passed through *this.
// 
// Note: prof.impl_->find_rec abstracts multi-theaded db use such that if a 
// given implementation requires a db per thread then find_rec will encapsulate
// that. This separation per function is 1 way of managing threading but a more
// extensible way of doing it is through a token or use of thread id in called
// function to map to a pool of available db objects transparently.
void card_reader_validation_simulation_load(Database::Profiler & prof)
{
    // keep going until card_reader_thread_exit_ is set to true
    assert(prof.card_reader_thread_exit_ == false);

    // SaltedKey must be owned by this thread only.
    const auto m = prof.impl_->stats_.requested_rec_count;
    SaltedKey sk(0, m);
    for (unsigned i = 0; i < m && !prof.card_reader_thread_exit_; ++i) {
        sk.key(i);
        prof.impl_->find_rec(sk); 
        if (i == (m - 1))
            i = 0;                  // wrap around again - loop until exit
    }
}

////////////////////////////////////////////////////////////////////////////////

void Database::Profiler::update_list_sim(void)
{
    // start reader thread - missed reads stats counted in each implemetation
#ifdef READER_THREAD
    std::thread card_reader_thread(&card_reader_validation_simulation_load, 
                                   std::ref(*this));
#endif

    // continue on with CRUD ops in main thread.
    enum {IMP_DELETE, IMP_CREATE, IMP_UPDATE};

    assert(impl_);
    assert(skey_);

    // db must be empty. Fix this - to do - uses the email from Raima. 
    //assert(!impl_->is_db_empty());

    // Note that this isn't about sim count... its about rec count to create
    // values outside of the range.
    // The M value is somewhat arbitrary but intended to be a number that
    // will always be a different key by using a seed that is larger than 
    // any seed of the the population created earlier with populate_db() 
    // above. 
    const unsigned M = 20000000 + 100; // impl_->stats_.requested_rec_count;
    const auto m = impl_->stats_.requested_sim_count; 

    auto n = impl_->stats_.requested_trans_grp_sz;
    assert(m > 0); 
    assert(n > 0);
    assert(!opts.impsim_csv_fn.empty());

    std::ofstream impsim_csv_log(opts.impsim_csv_fn, 
                                 std::ios::out | std::ios::trunc);

    // calculate number of transactions and track total to calculate 
    // record counts within each transaction including remainders
    time_t start, end;
    time(&start);         
    const unsigned trans_grps = (m + (n - 1)) / n;
    unsigned total = 0, vi = 0, new_rec_idx = m, s = 0, new_rec_seed = 20000000;
    for (unsigned int i = 0; i < trans_grps; ++i) {
        std::cout << "update list trans_grp # " << i + 1 << " of "<< trans_grps <<  std::endl;
        assert(m > total);

        if ((m - total) < n)    // last transaction group is not modulo n
            n = m - total;      // whats left is less than n, so update n once

        impl_->tx_begin();
        for (unsigned int j = 0; j < n; ++j) {

            // delete_rec, create_rec, update_rec in that order and known
            // apriori that for all cases - first the record must be found
            // then deleted or updated.
            // for a create record, increment from new_rec_idx
            // Warning: if the pop import file did not use keys generated from
            // key(total) then the key after sort will not be found. 
            // The key generated from the seed(total) could be sorted into
            // anywhere within the list, even at the (20M - 1) record. 
            if (s == IMP_DELETE) {
                skey_->key(total);
                impl_->delete_rec(*skey_); 
                s = IMP_CREATE;
            }
            else if (s == IMP_CREATE) {
                ++new_rec_seed;
                skey_->key(new_rec_seed);
                impl_->create_rec(*skey_);
                s = IMP_UPDATE;
            }
            else if (s == IMP_UPDATE) {
                skey_->key(total);
                impl_->update_rec(*skey_); 
                s = IMP_DELETE;
            }

            // checkpoint marker - update the csv log file with current record 
            // count and elapsed time up to this point.
            if (++total == opts.update_list_markers[vi]) {
                time(&end);
                time_t delta = difftime(end, start);
                impsim_csv_log << MK_STR(PROD) << "," 
                               << opts.update_list_markers[vi++] 
                               << "," << delta << std::endl;
            }
        }     
        impl_->tx_end();

    } // end outer for loop

    // optional flush used by McObject only - defaulted to nothing for others
    impl_->tx_sync();
    
#ifdef READER_THREAD
    // join as late as possible, block here while card reader exits
    card_reader_thread_exit_ = true;
    card_reader_thread.join();    
#endif
}

////////////////////////////////////////////////////////////////////////////////

// upon completion of this function all operating parameters are set.
void Database::Profiler::set_prof_opts(const int argc, 
                                       const char * const argv[])
{
    // Forming metrics log filename from the program name and adding a '
    // x-post-fix.csv onto the filename. Program name is unique per product
    // and target by design via the makefile support rules so csv files will 
    // be unique and bound by product and target attached to image name. 
    // set the defaults - simulation count and pop size can now diverge via
    // options overrides.
    std::string metrics_log_filename(argv[0]);
    strip_path(metrics_log_filename);
    opts.pop_csv_fn = metrics_log_filename + "-pop.csv";
    opts.impsim_csv_fn = metrics_log_filename + "-impsim.csv";

    // vector of sample points or markers set to default - copy entire vector
    // options over write values or they don't.
    opts.pop_markers = default_pop_markers;
    opts.update_list_markers = default_update_list_markers;

    // default size is last element in the default marker sample points 
    unsigned last_index = opts.pop_markers.size() - 1;
    opts.popsize = opts.pop_markers[last_index];

    last_index = opts.update_list_markers.size() - 1;
    opts.simcount = opts.update_list_markers[last_index];

    opts.trans_length = DEFAULT_DB_TRANS_LENGTH;

    // iterating  argv (argc - 1) times but allow for options to override
    // earlier options. 
    // @TODO : replace with table based on Options<Profiler::Options> via
    // reusable options module. 
    for (int i = 1; i < argc; ++i)
    {
        std::string arg(argv[i]);
        if (arg == "-p" || arg == "-P") {
            assert(i + 1 < argc);
            arg = argv[++i];
            opts.popsize = atoi(arg.c_str());
            assert(opts.popsize > 0);
        }
        else if (arg == "-s" || arg == "-S") {
            assert(i + 1 < argc);
            arg = argv[++i];
            opts.simcount = atoi(arg.c_str());
            assert(opts.simcount > 0);
        }
        else if (arg == "-t" || arg ==  "-T") {
            assert(i + 1 < argc);
            arg = argv[++i];
            opts.trans_length = atoi(arg.c_str());
            assert(opts.trans_length > 0);
        }
        else if (arg == "-f" || arg == "-F") {
            assert(i + 1 < argc);
            arg = argv[++i];
            opts.key_file = arg;
        }
        else if (arg == "-pm" || arg == "-PM") {
            assert(i + 1 < argc);
            arg = argv[++i];
            opts.pop_markers_filename = arg;
        }
        else if (arg ==  "-um" || arg ==  "-UM") {
            assert(i + 1 < argc);
            arg = argv[++i];
            opts.update_list_markers_filename = arg;
        }
        else {
            std::cout << "User Error: option " << arg << " not recognized\n";
            exit(-1);
        }
    } // end for loop

        // is there a pop markers file override ? 
    if (!opts.pop_markers_filename.empty()) {
        std::ifstream in(opts.pop_markers_filename.c_str());
        if (!in) {
            std::cout << "filename " << opts.pop_markers_filename 
                      << " not found!\n";
            exit(-1);
        }
        // copy numbers into a temporary vector
        // assign to options vector.
        std::vector<unsigned> markers{std::istream_iterator<unsigned>{in}, {}};
        opts.pop_markers = markers;
    }

    // either default or through a file override - one way or another - this 
    // vector gets set w/ ascending data markers or sample points. 
    assert(!opts.pop_markers.empty());
    validate_vector_values_ascending(opts.pop_markers);

    if (!opts.update_list_markers_filename.empty()) {
        std::ifstream in(opts.update_list_markers_filename.c_str());
        if (!in) {
            std::cout << "Bad option: filename " 
                      << opts.update_list_markers_filename << " not found!\n";
            exit(-1);
        }
        // copy numbers into a temporary vector
        // assign to options vector.
        std::vector<unsigned> markers{std::istream_iterator<unsigned>{in}, {}};
        opts.update_list_markers = markers;
    }

    assert(!opts.update_list_markers.empty());
    validate_vector_values_ascending(opts.update_list_markers);

} // end set_prof_opts

////////////////////////////////////////////////////////////////////////////////

// Calculations in earlier code retrieve in terms of total time required for
// processing. See earlier code
void Database::Profiler::print_stats()
{
    std::cout << "Stats post run: " << std::endl;
    std::cout << "\trequested rec count = " << impl_->stats_.requested_rec_count << std::endl;
    std::cout << "\trequested trans grp sz = " << impl_->stats_.requested_trans_grp_sz << std::endl;
    std::cout << "\tpop rec count = " << impl_->stats_.pop_rec_count << std::endl;
    std::cout << "\tcreates = " << impl_->stats_.creates << std::endl;
    std::cout << "\tdeletes = " << impl_->stats_.deletes << std::endl;
    std::cout << "\tupdates = " << impl_->stats_.updates << std::endl;
    std::cout << "\treads = " << impl_->stats_.reads << std::endl;
    std::cout << "\tmissed_reads = " << impl_->stats_.missed_reads << std::endl;
    std::cout << "\tsee csv files: " << opts.pop_csv_fn 
              << "\n\t-and-\n\t" 
              << opts.impsim_csv_fn << std::endl;

#ifdef DEBUG
    std::cout << "\tdiff_t = " << impl_->stats_.diff_t << std::endl;
    std::cout << "\twrite_diff_t = " << impl_->stats_.write_diff_t << std::endl;
    std::cout << "\tread_diff_t = " << impl_->stats_.read_diff_t << std::endl;
#endif
}

////////////////////////////////////////////////////////////////////////////////
// Impl interface
////////////////////////////////////////////////////////////////////////////////

Database::ProfilerImpl::ProfilerImpl() 
{
    // empty intentional
}

////////////////////////////////////////////////////////////////////////////////

// required for linking - pure virtual dtor implementation optional but 
// instantiating here for possible RAII usage.
Database::ProfilerImpl::~ProfilerImpl()
{
    // empty intentional
}

////////////////////////////////////////////////////////////////////////////////





