#ifndef DATABASE_PROFILER_HPP
#define DATABASE_PROFILER_HPP

#include <string>
#include <fstream>
#include <vector>
#include "saltedkey.hpp"

////////////////////////////////////////////////////////////////////////////////

// #ifdef XCOUT - inverts to not print with xcout
#ifdef XCOUT
#define xcout std::cout
#else
#define xcout false && std::cout
#endif

// this REC_COUNT is only used during initialization and overwritten by 
// vector anyways - not really needed anymore - todo: remove it.
#ifndef REC_COUNT
#define REC_COUNT (20 * 1000 * 1000) // 20,000,000
#endif

#ifndef TRANS_GRP_SZ
#define TRANS_GRP_SZ 10000
#endif

namespace Database {
class Profiler;
}

void card_reader_validation_simulation_load(Database::Profiler & prof);

namespace Database {

// factory pattern related functions. 
class ProfilerImpl * const createProfilerImpl(void);
void release(class ProfilerImpl * const impl);

class Profiler
{
public: 
    // public data for convenience - not recommended for production code
    struct Options
    {
        unsigned trans_length;              // transaction size before commit  
        unsigned popsize;                   // default is last vec value
        unsigned simcount;                  // default is last vec value
        std::string pop_markers_filename; 
        std::vector<unsigned> pop_markers;  // for each progressive sample size
        std::string update_list_markers_filename;
        std::vector<unsigned> update_list_markers;
        std::string key_file;               // Salted keys input filename
        std::string pop_csv_fn;
        std::string impsim_csv_fn;
    } opts;

    Profiler(const int argc, const char * const argv[]); 
    ~Profiler();

    void print_opts(void);
    bool open_db(const unsigned number_of_threads = 2);
    bool is_db_empty(); 

    // create a set of unique records based on max and intermediate markers for
    // performance measurement on elapsed time between markers or sample points. 
    void populate_db(void);  

    // import simulation where loaded implies concurrent reads 
    // concurrently operating to validate cards for transit pass - 2 threads
    // uses intermediate markers or sample points in which to gather metrics
    // based on elapsed time. 
    void update_list_sim(void);

    void print_stats();

private : 

    void set_prof_opts(const int argc, const char * const argv[]);

    // class CardInfo * impl_;      // Ideally manages db object types.
    // General container for some unknown cardinality of db object types.
    class ProfilerImpl * impl_;     // GoF - Bridge Pattern - Handle/Body idiom.
    SaltedKey * skey_;

    volatile bool card_reader_thread_exit_;
    friend void ::card_reader_validation_simulation_load(Database::Profiler &);
};


////////////////////////////////////////////////////////////////////////////////

/// @TODO:
// Ideally this ProfilerImpl isn't required, it abstracts away the number of 
// db objects managed for a given product - rdm, sqlite or other
// Ideally however it wouldn't be required and for each Db Object type there 
// an impl for that particular Db Object type with CRUD properties. Data is
// read into or out of that object's internal state from the database or the
// object itself is deleted. In fact this class can be parameterized around
// the object type T itself, using templates <T> to abstract away types and
// operations. An object type wrapper would abstract away the specifics of a
// given db implementation and support multiple db object types being managed
// by a container like Profiler above. 
// This generalized implementation wrapper around types created for each db is
// however sufficient to generalize the performance analysis. 
class ProfilerImpl
{

protected: 
    enum Run_mode {ConcurrentCRUD, CreateOnly, ReadOnly};
    struct Stats 
    {
        // m = nq + r, m:requested_rec_count, n:requested_trans_grp_sz
        unsigned requested_rec_count; // pop
        unsigned requested_sim_count;
        unsigned requested_trans_grp_sz; 
        unsigned pop_rec_count;
        unsigned sim_rec_count;
        unsigned creates;
        unsigned deletes;
        unsigned updates;
        unsigned reads; 
        unsigned missed_reads;
        double diff_t;
        double write_diff_t;
        double read_diff_t;
    } stats_ = {REC_COUNT, TRANS_GRP_SZ};

    ProfilerImpl();
    virtual ~ProfilerImpl() = 0;

    virtual bool open_db(const unsigned number_of_threads) = 0; 
    virtual bool is_db_empty() { return true; }

    virtual void tx_begin() = 0;
    virtual void create_rec(const SaltedKey& sk) = 0;
    virtual void find_rec(const SaltedKey& sk) = 0;
    virtual void update_rec(const SaltedKey& sk) = 0;
    virtual void delete_rec(const SaltedKey& sk) = 0; 
    virtual void tx_end() = 0;

    // created, read, update, delete ops (crud) while another thread validates
    // card salted key record lookups. Only few implements this default virtual
    // function
    virtual void tx_sync() {}

private : 
    friend class Profiler;
    friend void ::card_reader_validation_simulation_load(Database::Profiler &);

    friend class ProfilerImpl * const createProfilerImpl(void);
    friend void release(class ProfilerImpl * const impl);
};

} // end namespace

#endif // DATABASE_PROFILER_HPP



