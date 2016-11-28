// File: sqlite-db.cpp
// No type safety whatsoever in this module - as strings are used to support
// CRUD queries. If a string isn't right - an exception will be thrown instead
// of a compiler error. This is the nature of sqlite3 whereas other API based
// databases such as OODBMS are based on types.
//
// see cards_db.sql
/**
create table card_info(
    card_access_type char, 
    token_digest char(36) primary key not null,
    last_digts char(4),
    access_rules blob(500)
    );
*/ 


#include "sqlite-db.hpp"
#include "oosqlite3.hpp"

#include <iostream>
#include <cassert>

static const char * const dbfile = "cards.db";

// INSERT INTO card_info VALUES (0, 'ABCD', '0000', '000');
static const char * const begintx = "begin transaction;";
static const char * const endtx = "commit transaction;"; 

////////////////////////////////////////////////////////////////////////////////

Database::SQLITE_ProfilerImpl::SQLITE_ProfilerImpl(void)
{
}

////////////////////////////////////////////////////////////////////////////////

Database::SQLITE_ProfilerImpl::~SQLITE_ProfilerImpl()
{
}

////////////////////////////////////////////////////////////////////////////////

bool Database::SQLITE_ProfilerImpl::open_db(const unsigned number_of_threads)
{
    try {
        rdb_.open(dbfile);
        wdb_.open(dbfile);
    }
    catch (CppSQLite3Exception& ex)
    {
        std::cerr << ex.errorCode() << ":" << ex.errorMessage() << std::endl;
        return false;
    }
    return true;
}

////////////////////////////////////////////////////////////////////////////////

void Database::SQLITE_ProfilerImpl::tx_begin()
{
    try {
        wdb_.execDML(begintx);
    }
    catch (CppSQLite3Exception & ex)
    {
        std::cerr << ex.errorCode() << ":" << ex.errorMessage() << std::endl;
        assert(!"unexpected tx begin exception in sqlite3");
    }
}

////////////////////////////////////////////////////////////////////////////////

// since sqlite doesn't create a struct definition - its sufficient to 
// hardcode some data.
void Database::SQLITE_ProfilerImpl::create_rec(const SaltedKey& sk)
{
    const char * const keystr = sk.key();
    assert(strlen(keystr) == (SALTED_KEY_SZ - 1));
    std::string key(keystr);

    // This type of insert is more efficient than multiple fields
    std::string q = "INSERT INTO card_info VALUES (0, ";
   
    q += "'" + key;
    q += "', '0001', '1000');";
    xcout << "q = " << q << std::endl;

    try {
        const int nRows = wdb_.execDML(q.c_str());
        assert(nRows == 1);
        xcout << "nRows = " << nRows << std::endl;
    }
    catch (CppSQLite3Exception & ex)
    {
        std::cerr << ex.errorCode() << ":" << ex.errorMessage() << std::endl;
        assert(!"unexpected create record exception in sqlite3");
    }
}

////////////////////////////////////////////////////////////////////////////////

// https://www.tutorialspoint.com/sqlite/sqlite_update_query.htm
// UPDATE COMPANY SET ADDRESS = 'Texas', X = ? WHERE ID = 6;
void Database::SQLITE_ProfilerImpl::update_rec(const SaltedKey& sk)
{
    std::string qstr = "update card_info set access=1,last_digits='1111'";
    qstr += ",access_rules='0000000001' where token_digest=";
    const char * salted_key = sk.key();
    std::string token = "'" + std::string(salted_key) + "';";
    qstr += token;

    try {
        // std::cout << "qstr = " << qstr << std::endl;
        CppSQLite3Query q = wdb_.execQuery(qstr.c_str());
        stats_.reads++;
    }
    catch (CppSQLite3Exception & ex)
    {
        //std::cerr << ex.errorCode() << ":" << ex.errorMessage() << std::endl;
        //assert(!"unexpected update record exception in sqlite3");
        stats_.missed_reads++;
    }
}

////////////////////////////////////////////////////////////////////////////////

// https://www.tutorialspoint.com/sqlite/sqlite_delete_query.htm
void Database::SQLITE_ProfilerImpl::delete_rec(const SaltedKey& sk)
{
    std::string qstr = "delete from card_info where token_digest=";
    const char * salted_key = sk.key();
    std::string token = "'" + std::string(salted_key) + "';";
    qstr += token;

    try {
        // std::cout << "qstr = " << qstr << std::endl;
        CppSQLite3Query q = wdb_.execQuery(qstr.c_str());
        stats_.deletes++;
    }
    catch (CppSQLite3Exception & ex)
    {
        std::cerr << ex.errorCode() << ":" << ex.errorMessage() << std::endl;
        assert(!"unexpected delete record exception in sqlite3");
    }
}

////////////////////////////////////////////////////////////////////////////////

// https://www.tutorialspoint.com/sqlite/sqlite_select_query.htm
// uses read-only db required per multi-threading requirements. 
void Database::SQLITE_ProfilerImpl::find_rec(const SaltedKey& sk)
{
    std::string qstr = "select * from card_info where token_digest=";
    const char * salted_key = sk.key();
    std::string token = "'" + std::string(salted_key) + "';";
    qstr += token;

    try {
        // std::cout << "qstr = " << qstr << std::endl;
        CppSQLite3Query q = rdb_.execQuery(qstr.c_str());
        stats_.reads++;
    }
    catch (CppSQLite3Exception & ex)
    {
        stats_.missed_reads++;
    }
}

////////////////////////////////////////////////////////////////////////////////

void Database::SQLITE_ProfilerImpl::tx_end()
{
    try {
        wdb_.execDML(endtx);
    }
    catch (CppSQLite3Exception & ex)
    {
        std::cerr << ex.errorCode() << ":" << ex.errorMessage() << std::endl;
        assert(!"unexpected tx end exception in sqlite3");
    }
}

////////////////////////////////////////////////////////////////////////////////

// if I do need cfg information - I can supply a struct argument by const ref
// and let the structure vary the detail
Database::ProfilerImpl * const Database::createProfilerImpl() 
{
    ProfilerImpl * const impl = new SQLITE_ProfilerImpl;
    return impl;
}

void Database::release(Database::ProfilerImpl * const impl) 
{
    delete impl;
}

