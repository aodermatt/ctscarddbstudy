#include "rdm.h"
#include "cardsdb_structs.h"
#include "cardsdb_api.h"
#include "database_profiler.hpp"

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
    // has to be located here or core dump on exit for older version of rdm14
    // fixed in later version so ordering is not important here. 
    RDM_CPP::TFS tfs;   
    RDM_CPP::Db_cardsdb w_cards_db_, r_cards_db_;
    RDM_CPP::Cursor_card_info c_find_, c_update_, c_delete_;
    bool db_opened_;
};

} // end namespace Database


