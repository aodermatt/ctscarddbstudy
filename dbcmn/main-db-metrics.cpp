#include "dbexception.hpp"
#include "database_profiler.hpp"
#include <iostream>
#include <string>
#include <cassert>
#include <vector>

void help(const char * const program);

////////////////////////////////////////////////////////////////////////////////

int main(int argc, char * argv[])
{
    try {
        if (argc > 1 && std::string(argv[1]) == "-help") {
            help(argv[0]); 
            return 0;
        }

        Database::Profiler prof(argc, argv);
        prof.print_opts();

        // opens one or more db's for multi-threaded usage
        const bool rc = prof.open_db();
        assert(rc == true && "open_db() failed");

        const bool db_empty = prof.is_db_empty();
        if (db_empty) {
            std::cout << "\nStarting Populating database...\n"; 
            prof.populate_db();
        }
        else {
            std::cout << "\nNote: db must be empty to run all performance tests\n";
            std::cout << "initialize the database before running test\n";
            //return -1;
        }

        // import new list concurrent with read validation of transit cards
        std::cout << "\nStarting Update List Simulation...\n";
        prof.update_list_sim();
        prof.print_stats();
    }

    // each Database throws an specific exception, this macro generalizes that.
    DB_CATCH_EXCEPTION_CLAUSE

    catch (...) 
    {
        std::cout << "unknown exception ..." << std::endl;
    }

    return 0;
}


