#include "rdm14-db.hpp"
#include <iostream>
#include <assert.h>
#include <cstring>

#ifndef DB_PATH
#define DB_PATH "cardsdb"
#endif

using namespace RDM_CPP;
#ifndef DIRTY_CACHE_REFRESH
#define DIRTY_CACHE_REFRESH 300     // 1/3rd of second - 3x default
#endif        

////////////////////////////////////////////////////////////////////////////////

Database::RDM_ProfilerImpl::RDM_ProfilerImpl() 
         : db_opened_(false)
{
    // std::cout << "Database::RDM_ProfilerImpl::RDM_ProfilerImpl() called" << std::endl;
    // rdm_tlsVersion();
}

////////////////////////////////////////////////////////////////////////////////

Database::RDM_ProfilerImpl::~RDM_ProfilerImpl()
{
    // std::cout << "Database::RDM_ProfilerImpl::~RDM_ProfilerImpl() called" << std::endl;
}

////////////////////////////////////////////////////////////////////////////////

bool Database::RDM_ProfilerImpl::is_db_empty()
{
    if (!db_opened_) {
        std::cout << "Error: is_db_empty() - db is not yet opened" << std::endl;
        return false;
    }

    uint64_t row_count = r_cards_db_.Get_card_info_Rows().GetCount(); 

    // if (row_count) 
    std::cout << "record count for database = " << row_count << std::endl;

    return row_count == 0; 
}

////////////////////////////////////////////////////////////////////////////////

// To support multi-threading 2 db instances per thread must be created.
// Similar to sqlite3
// v12 prints to std out: Document Root: /Users/ascheurer/cubic/db2/deploy/
// This annoying message is removed in rdm v14
bool Database::RDM_ProfilerImpl::open_db(const unsigned number_of_threads)
{
    bool status = true;
    try {
        tfs = TFS::Alloc("");
        w_cards_db_ = tfs.AllocDatabase();
        w_cards_db_.Open("cardsdb", RDM_OPEN_SHARED);
        c_delete_ = w_cards_db_.Get_card_info_RowsBy_token_digest();
        c_update_ = w_cards_db_.Get_card_info_RowsBy_token_digest();

        r_cards_db_ = tfs.AllocDatabase();
        r_cards_db_.Open("cardsdb", RDM_OPEN_SHARED_DIRTY);
        c_find_ = r_cards_db_.Get_card_info_RowsBy_token_digest();
        //r_cards_db_.SetDirtyReadRefresh(DIRTY_CACHE_REFRESH);  
    }
    catch (const rdm_exception& ex) {
       std::cout << "rdm open_db() exception caught - reason: " 
                 << ex.what() << std::endl;
       status = false; 
    }

    db_opened_ = true;
    return status;
}

////////////////////////////////////////////////////////////////////////////////

void Database::RDM_ProfilerImpl::tx_begin()
{
    w_cards_db_.StartUpdate(RDM_LOCK_ALL);
}

////////////////////////////////////////////////////////////////////////////////

void Database::RDM_ProfilerImpl::create_rec(const SaltedKey& sk)
{
    static int i = 0;
    ++i;

    const char * key = sk.key();
    RDM_CPP::Cursor_card_info r = c_update_;
    r.MoveTo_token_digest((const uint8_t *)key); 
    //assert(r.GetStatus() == CURSOR_AT_ROW);
    if (r.GetStatus() == CURSOR_AT_ROW) {
        return;
    }

    // create bit variations in card type and list type.
    unsigned char access = 0;       // high and low nybble are 0
    if (i % 2) 
        access |= (1 << 4);         // set high nybble to 1
    else
        access |= 1;                // set low nybble to 1

    CARD_INFO ci = {0};
    ci.card_access_type = access;

    assert(strlen(key) == (SALTED_KEY_SZ - 1));
    std::memcpy(ci.token_digest, key, sizeof(ci.token_digest));
    ci.last_digits[0] = '0';
    ci.last_digits[1] = '1';
    ci.last_digits[2] = '2';
    ci.last_digits[3] = '3';

    // Note: why the #if 1/0 ?
    // After a newly populated database and the update list simulation is
    // run and a new key exists, not in the db, then Insert_card_info_Row(ci)
    // causes an rdm exception: std::exception - whatever that means. 
    // note that the reader thread if active will cause a 
    // terminate called without an active exception
    // This happens on the first salted key to be put in the database
    // however this does not happen if the db is empty of all records, pop
    // happens followed by the update list simulation with an active reader
    // thread. 
    //std::cout << "create_rec salted key = " << key << std::endl;
    w_cards_db_.Insert_card_info_Row(ci);
    ++stats_.creates;
}

////////////////////////////////////////////////////////////////////////////////

// Uses read-only db - missed reads are normal given the dirty read caching 
// model unique to raima. 
void Database::RDM_ProfilerImpl::find_rec(const SaltedKey& sk)
{
    const char * key = sk.key();
    RDM_CPP::Cursor_card_info r = c_find_;
    r.MoveTo_token_digest((const uint8_t *)key); 
    if (r.GetStatus() == CURSOR_AT_ROW) {
            CARD_INFO fields = {0};
            r.ReadRow(fields);
            ++stats_.reads;
    }
    // no record found - timestamp read record not found. 
    else {
        ++stats_.missed_reads;
    }
}

////////////////////////////////////////////////////////////////////////////////

void Database::RDM_ProfilerImpl::update_rec(const SaltedKey& sk)
{
    const char * key = sk.key();
    RDM_CPP::Cursor_card_info r = c_update_;
    r.MoveTo_token_digest((const uint8_t *)key); 
    //assert(r.GetStatus() == CURSOR_AT_ROW);
    if (r.GetStatus() != CURSOR_AT_ROW) {
        return;
    }

    // update only a select set of fields. Raima optimizes writes to include
    // only a subset of fields however assume worst case here. 
    CARD_INFO fields = {0};
    r.ReadRow(fields);
    fields.card_access_type = 255;
    fields.last_digits[0] = 'w'; 
    fields.last_digits[1] = 'x'; 
    fields.last_digits[2] = 'y'; 
    fields.last_digits[3] = 'z'; 

    // token_digest same as key above - don't need to set again as setting 
    // again would duplicate what is already there!!!
    // std::memcpy(fields.token_digest, key, sizeof(fields.token_digest));
    // assert(!memcmp(fields.token_digest, key, sizeof(fields.token_digest)));

    // Equivalent to a write and a transaction is needed for this write as it
    // is with new or inserted record.
    r.UpdateRow(fields);
    ++stats_.updates;
}

////////////////////////////////////////////////////////////////////////////////

void Database::RDM_ProfilerImpl::delete_rec(const SaltedKey& sk)
{
    const char * key = sk.key();
    RDM_CPP::Cursor_card_info r = c_delete_;
    r.MoveTo_token_digest((const uint8_t *)key); 
    //assert(r.GetStatus() == CURSOR_AT_ROW);
    if (r.GetStatus() == CURSOR_AT_ROW) {
        // write transaction - remove the record. 
        r.DeleteRow();
        ++stats_.deletes;
    }
}

////////////////////////////////////////////////////////////////////////////////

void Database::RDM_ProfilerImpl::tx_end()
{
    w_cards_db_.End();
}

////////////////////////////////////////////////////////////////////////////////

// if I do need cfg information - I can supply a struct argument by const ref
// and let the structure vary the detail
Database::ProfilerImpl * const Database::createProfilerImpl() 
{
    ProfilerImpl * const impl = new RDM_ProfilerImpl;
    // std::cout << "impl ptr = " << impl << std::endl;
    return impl;
}

////////////////////////////////////////////////////////////////////////////////

void Database::release(Database::ProfilerImpl * const impl) 
{
    // std::cout << "impl ptr = " << impl << std::endl;
    delete impl;
}

