#include "rdm12-db.hpp"
#include <iostream>
#include <assert.h>
#include <cstring>

#ifndef DB_PATH
#define DB_PATH "cardsdb"
#endif

#ifndef DIRTY_CACHE_REFRESH
#define DIRTY_CACHE_REFRESH 300     // 1/3rd of second - 3x default
#endif        

////////////////////////////////////////////////////////////////////////////////

Database::RDM_ProfilerImpl::RDM_ProfilerImpl(void)
        : db_opened_(false)
{
}

////////////////////////////////////////////////////////////////////////////////

Database::RDM_ProfilerImpl::~RDM_ProfilerImpl()
{
}


bool Database::RDM_ProfilerImpl::is_db_empty()
{
    if (!db_opened_) {
        std::cout << "Error: is_db_empty() - db is not yet opened" << std::endl;
        return false;
    }

    uint64_t row_count = r_cards_db_.Get_card_info_records().GetCount();
    if (row_count) 
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
        w_cards_db_ = RDM_CPP::Db_cardsdb::Open(DB_PATH, RDM_OPEN_SHARED);

        r_cards_db_ = RDM_CPP::Db_cardsdb::Open(DB_PATH, RDM_OPEN_SHARED);
        r_cards_db_.SetDirtyReadRefresh(DIRTY_CACHE_REFRESH);  
    }
    catch (const RDM_CPP::rdm_exception& ex) {
       std::cout << "rdm open_db() exception caught - reason: " 
                 << ex.what() << std::endl;
       status = true; 
    }

    db_opened_ = true;
    return status;
}

////////////////////////////////////////////////////////////////////////////////

void Database::RDM_ProfilerImpl::tx_begin()
{
    w_cards_db_.BeginUpdate();
}

////////////////////////////////////////////////////////////////////////////////

void Database::RDM_ProfilerImpl::create_rec(const SaltedKey& sk)
{
    static int i = 0;

    // create bit variations in card type and list type.
    unsigned char access = 0;       // high and low nybble are 0
    if (i % 2) 
        access |= (1 << 4);         // set high nybble to 1
    else
        access |= 1;                // set low nybble to 1

    struct card_info ci = {{0}};
    ci.card_access_type = access;

    const char * card_salted_key = sk.key();
    // std::cout << "key = " << card_salted_key << std::endl;
    assert(strlen(card_salted_key) == (SALTED_KEY_SZ - 1));
    std::memcpy(ci.token_digest, card_salted_key, sizeof(ci.token_digest));

    //std::cout << "w";
    w_cards_db_.New_card_info_record(ci);
    ++stats_.updates;
    ++i;
}

////////////////////////////////////////////////////////////////////////////////

// Uses read-only db - missed reads are normal given the dirty read caching 
// model unique to raima. 
void Database::RDM_ProfilerImpl::find_rec(const SaltedKey& sk)
{
    const char * key = sk.key();
    RDM_CPP::Cursor_card_info r = r_cards_db_.Get_card_info_records();

    r.KeyFindBy_token_digest((const uint8_t *)key); 
    if (r.CheckPosition() == CURSOR_AT_RECORD) {
            struct card_info fields = {{0}};
            r.GetFieldValues(fields);
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
    RDM_CPP::Cursor_card_info r = w_cards_db_.Get_card_info_records();
    r.KeyFindBy_token_digest((const uint8_t *)key); 
    assert(r.CheckPosition() == CURSOR_AT_RECORD);

    // update only a select set of fields. Raima optimizes writes to include
    // only a subset of fields however assume worst case here. 
    struct card_info fields = {{0}};
    r.GetFieldValues(fields);
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
    r.SetFieldValues(fields);
    ++stats_.updates;

}

////////////////////////////////////////////////////////////////////////////////

void Database::RDM_ProfilerImpl::delete_rec(const SaltedKey& sk)
{
    const char * key = sk.key();
    RDM_CPP::Cursor_card_info r = w_cards_db_.Get_card_info_records();
    r.KeyFindBy_token_digest((const uint8_t *)key); 
    assert(r.CheckPosition() == CURSOR_AT_RECORD);

    // write transaction - remove the record. 
    r.Delete();
    ++stats_.deletes;
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
    return impl;
}

void Database::release(Database::ProfilerImpl * const impl) 
{
    delete impl;
}

