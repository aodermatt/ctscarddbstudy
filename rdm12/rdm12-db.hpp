#include "database_profiler.hpp"
#include "rdm.h"
#include "cardsdb.h"
#include "cardsdb_api.h"

namespace Database {

class RDM_ProfilerImpl : public ProfilerImpl 
{
public:
    //  RDM_ProfilerImpl(const std::string & metrics_log_filename);
    RDM_ProfilerImpl(); 
    ~RDM_ProfilerImpl();
    bool is_db_empty(); 

    bool open_db(const unsigned number_of_threads);

    void tx_begin();
    void create_rec(const SaltedKey& sk);
    void update_rec(const SaltedKey& sk);
    void delete_rec(const SaltedKey& sk);
    void tx_end();

    void find_rec(const SaltedKey& sk);

private:
    //std::string & metrics_log_filename_;
    RDM_CPP::Db_cardsdb w_cards_db_, r_cards_db_;
    bool db_opened_;
};

} // end namespace Database


