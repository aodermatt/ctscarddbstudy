#include "mco-db.hpp"

////////////////////////////////////////////////////////////////////////////////

Database::MCO_ProfilerImpl::MCO_ProfilerImpl(void)
        : database(0), con(0), t(0)
{
}

////////////////////////////////////////////////////////////////////////////////

Database::MCO_ProfilerImpl::~MCO_ProfilerImpl()
{
    // order is important here - see ctor order initialization
    // reverse order for dtor
    delete t;
    delete con;
    delete con2;
    delete database;
}

////////////////////////////////////////////////////////////////////////////////

bool Database::MCO_ProfilerImpl::open_db(const unsigned number_of_threads)
{
    database = new MCODatabase(MCO_DBNAME);
    con = new MCOConnection(*database);
    con2 = new MCOConnection(*database);


    // set prior to import
    con->set_commit_policy(MCO_COMMIT_NO_SYNC);
    t = new MCOTransaction(*con);

    return true;
}

////////////////////////////////////////////////////////////////////////////////

void Database::MCO_ProfilerImpl::tx_begin()
{
    t->start(MCO_READ_WRITE);
}

////////////////////////////////////////////////////////////////////////////////

void Database::MCO_ProfilerImpl::create_rec(const SaltedKey& sk)
{
    const char * key = sk.key();
    assert(strlen(key) == SALTED_KEY_SZ - 1);
    CHECK(le.create(*t));
    CHECK(le.salted_key_put(key, SALTED_KEY_SZ - 1));
    CHECK(le.is_good_put(0));
    CHECK(le.meta_info_put(0));
}

////////////////////////////////////////////////////////////////////////////////

void Database::MCO_ProfilerImpl::update_rec(const SaltedKey& sk)
{
    uint1 is_good;
    uint8 meta_info;
    const char * key = sk.key();
    assert(strlen(key) == SALTED_KEY_SZ - 1);

    testdb::ListEntry le;
    MCO_RET rc = testdb::ListEntry::by_salted_key::find(*t, key, 
                                                        SALTED_KEY_SZ - 1, le);

    if (rc == MCO_S_OK) {
        /* Update record */
        CHECK(le.is_good_get(is_good));
        CHECK(le.meta_info_get(meta_info));
        is_good = ++is_good  % 2;
        meta_info = ++meta_info % 255;
        CHECK(le.is_good_put(is_good));
        CHECK(le.meta_info_put(meta_info));
    } else if (rc != MCO_S_NOTFOUND) {
        CHECK(rc);
        assert(!"unexpected MCO_S_NOTFOUND in update rec");
    }
    // no write or update function - just set the fields evidently similar
    // raima - an update or write doesn't exist as it does with sqlite and
    // other embedded db's I've worked with. Even Raima has a d_recwrite 
    // function that is perhaps not used here but has a SetFieldValues
//    CHECK(le.salted_key_put(key, SALTED_KEY_SZ - 1));
//    CHECK(le.is_good_put(1));
//    CHECK(le.meta_info_put(1));

}

////////////////////////////////////////////////////////////////////////////////

void Database::MCO_ProfilerImpl::delete_rec(const SaltedKey& sk)
{
    // char key[SALTED_KEY_SZ];
    testdb::ListEntry le;

    // rand_key(seed, key);
    const char * key = sk.key(); 
    assert(strlen(key) == (SALTED_KEY_SZ - 1));
    MCO_RET rc = testdb::ListEntry::by_salted_key::find(*t, key, 
                                                        SALTED_KEY_SZ - 1, le);
    if (rc == MCO_S_OK) {
        /* Delete record */
        CHECK(le.remove());
    } else if (rc != MCO_S_NOTFOUND) {
        CHECK(rc);
        assert(!"unexpected MCO_S_NOTFOUND in delete rec");
    }

}
////////////////////////////////////////////////////////////////////////////////

// Evidently reads require a transaction of read-only
void Database::MCO_ProfilerImpl::find_rec(const SaltedKey& sk)
{
    //assert(con);

    // char key[SALTED_KEY_SZ];
    static MCOTransaction tx(*con2);
    testdb::ListEntry le;

    // rand_key(seed, key);
    const char * key = sk.key();
    assert(strlen(key) == (SALTED_KEY_SZ - 1));
    tx.start(MCO_READ_ONLY);
    MCO_RET rc = testdb::ListEntry::by_salted_key::find(tx, key, 
                                                        SALTED_KEY_SZ - 1, le);
    if (rc == MCO_S_OK) {
        uint1 is_good;
        uint8 meta_info;
        /* Get other fields */
        CHECK(le.is_good_get(is_good));
        CHECK(le.meta_info_get(meta_info));
    } 
    else if (rc != MCO_S_NOTFOUND) {
        CHECK(rc);
        assert(!"unexpected MCO_S_NOTFOUND in find rec");
    }

    tx.commit();
}

////////////////////////////////////////////////////////////////////////////////


void Database::MCO_ProfilerImpl::tx_end()
{
    t->commit();
}

////////////////////////////////////////////////////////////////////////////////

void Database::MCO_ProfilerImpl::tx_sync()
{
    // called after populating the db is completed
    con->set_commit_policy(MCO_COMMIT_SYNC_FLUSH);  
}

////////////////////////////////////////////////////////////////////////////////
//
// Factory based free functions
//
////////////////////////////////////////////////////////////////////////////////
 
Database::ProfilerImpl * const Database::createProfilerImpl() 
{
    ProfilerImpl * const impl = new MCO_ProfilerImpl;
    return impl;
}

////////////////////////////////////////////////////////////////////////////////

void Database::release(Database::ProfilerImpl * const impl) 
{
    delete impl;
}

