// File: sqlite-db.cpp

#include "database_profiler.hpp"
#include "oosqlite3.hpp"

namespace Database {

class SQLITE_ProfilerImpl : public ProfilerImpl 
{
public:
    //  SQLITE_ProfilerImpl(const std::string & metrics_log_filename);
    SQLITE_ProfilerImpl(); 
    ~SQLITE_ProfilerImpl();

    bool open_db(const unsigned number_of_threads);

    void tx_begin();
    void create_rec(const SaltedKey& sk);
    void update_rec(const SaltedKey& sk);
    void delete_rec(const SaltedKey& sk);
    void tx_end();

    void find_rec(const SaltedKey& sk);

private:
    //std::string & metrics_log_filename_;
    CppSQLite3DB rdb_, wdb_;
};

} // end namespace Database


