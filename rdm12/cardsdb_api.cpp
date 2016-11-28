#include "cardsdb_api.h"
using namespace RDM_CPP;

Db_cardsdb Db_cardsdb::Open (RDM_OPEN_MODE mode, const void *dbd_array, int32_t dbdsize, const ENC *enc) throw (const rdm_exception&) {
#if !defined(RDM_NO_UNICODE)
    return Db::_OpenDatabase (Type (), L"cardsdb", mode, dbd_array, dbdsize, enc);
#else
    return Db::_OpenDatabase (Type (), "cardsdb", mode, dbd_array, dbdsize, enc);
#endif /*RDM_NO_UNICODE*/

}

Db_cardsdb Db_cardsdb::Open (const char *name, RDM_OPEN_MODE mode, const void *dbd_array, int32_t dbdsize, const ENC *enc) throw (const rdm_exception&) {
    return Db::_OpenDatabase (Type (), name, mode, dbd_array, dbdsize, enc);
}

#if !defined(RDM_NO_UNICODE)
Db_cardsdb Db_cardsdb::Open (const wchar_t *name, RDM_OPEN_MODE mode, const void *dbd_array, int32_t dbdsize, const ENC *enc) throw (const rdm_exception&) {
    return Db::_OpenDatabase (Type (), name, mode, dbd_array, dbdsize, enc);
}
#endif /*RDM_NO_UNICODE*/

dbType Db_cardsdb::Type (void) {
    static char const type = '\0';
    return &type;
}

Db_cardsdb::Db_cardsdb (void) throw () {
}

Db_cardsdb::Db_cardsdb (const Db& db) throw () : Db (db, Type()) {
}

Db_cardsdb::Db_cardsdb (const Db_cardsdb& db) throw () : Db (db) {
}

Db_cardsdb::Db_cardsdb (IDb *idb) : Db (idb) {
}

Db_cardsdb& Db_cardsdb::operator = (const Db& db) throw (const rdm_exception&) {
    return static_cast<Db_cardsdb&>(_AssignAndVerifyType (Type (), db)); /*lint !e1772 ('*this' is being returned from the called function) */ /*lint !e1774 (AssignedAndVerifyType will make sure this is the right type, so static_check is sufficient) */
} /*lint !e1529 (checking for assignment to 'this' in the called function) */

Db_cardsdb& Db_cardsdb::operator = (const Db_cardsdb& db) throw () {
    return static_cast<Db_cardsdb&>(_AssignAndVerifyType (Type (), static_cast<const Db&>(db))); /*lint !e1772 ('*this' is being returned from the called function) */ /*lint !e1774 (AssignedAndVerifyType will make sure this is the right type, so static_check is sufficient) */
} /*lint !e1529 (checking for assignment to 'this' in the called function) */

Db_cardsdb::~Db_cardsdb () {
}

Cursor_card_info Db_cardsdb::New_card_info_record (const struct card_info& fields) const throw (const rdm_exception&) {
    return Cursor_card_info (_NewRecords (Cursor_card_info::Type (), &fields));
}

Cursor_card_info Db_cardsdb::New_card_info_record (void) const throw (const rdm_exception&) {
    return Cursor_card_info (_NewRecords (Cursor_card_info::Type ()));
}

Cursor_card_access_rules Db_cardsdb::New_card_access_rules_record (const struct card_access_rules& fields) const throw (const rdm_exception&) {
    return Cursor_card_access_rules (_NewRecords (Cursor_card_access_rules::Type (), &fields));
}

Cursor_card_access_rules Db_cardsdb::New_card_access_rules_record (void) const throw (const rdm_exception&) {
    return Cursor_card_access_rules (_NewRecords (Cursor_card_access_rules::Type ()));
}

Cursor_card_info Db_cardsdb::Get_card_info_records (const DB_ADDR& dba) const throw (const rdm_exception&) {
    return Cursor_card_info (_GetRecords (Cursor_card_info::Type (), &dba));
}

Cursor_card_access_rules Db_cardsdb::Get_card_access_rules_records (const DB_ADDR& dba) const throw (const rdm_exception&) {
    return Cursor_card_access_rules (_GetRecords (Cursor_card_access_rules::Type (), &dba));
}

Cursor_card_info Db_cardsdb::Get_card_info_recordsBy_token_digest (const uint8_t token_digest_val[35]) const throw (const rdm_exception&)
{
    return _GetRecordsByKey (TOKEN_DIGEST, token_digest_val, sizeof(uint8_t) * 35);
}

Cursor_card_info Db_cardsdb::Get_card_info_recordsBy_token_digest () const throw (const rdm_exception&) {
    return Cursor_card_info (_GetRecordsByKey (TOKEN_DIGEST));
}

Cursor_card_info Db_cardsdb::Get_card_info_recordsBy_token_digest_inRange (const uint8_t token_digest_start_val[35], const uint8_t token_digest_end_val[35]) const throw (const rdm_exception&)
{
    return _GetRecordsByKeyInRange(TOKEN_DIGEST, token_digest_start_val, sizeof(uint8_t) * 35, 0, 0, token_digest_end_val, sizeof(uint8_t) * 35, 0, 0);
}

recordType Cursor_card_info::Type (void) {
    return CARD_INFO;
}

Cursor_card_info::Cursor_card_info (void) throw () {
}

Cursor_card_info::Cursor_card_info (const Cursor& cursor) throw (const rdm_exception&) : Cursor (cursor, Type ()) {
}

Cursor_card_info::Cursor_card_info (const Cursor_card_info& cursor) throw () : Cursor (cursor) {
}

Cursor_card_info& Cursor_card_info::operator = (const Cursor& cursor) throw (const rdm_exception&) {
    return static_cast<Cursor_card_info&>(_AssignAndVerifyType (Type (), cursor)); /*lint !e1772 ('*this' is being returned from the called function) */ /*lint !e1774 (_AssignAndVerifyType will make sure this is the right type, so static_check is sufficient) */
} /*lint !e1529 (checking for assignment to 'this' in the called function) */

Cursor_card_info& Cursor_card_info::operator = (const Cursor_card_info& cursor) throw () {
    return static_cast<Cursor_card_info&>(_AssignAndVerifyType (Type (), static_cast<const Cursor&>(cursor))); /*lint !e1772 ('*this' is being returned from the called function) */ /*lint !e1774 (AssignedAndVerifyType will make sure this is the right type, so static_check is sufficient) */
} /*lint !e1529 (checking for assignment to 'this' in the called function) */

Cursor_card_info Cursor_card_info::GetRecordsBy_token_digest () const throw (const rdm_exception&) {
    return Cursor_card_info (_GetRecordsByKey (TOKEN_DIGEST));
}

Cursor_card_info Cursor_card_info::GetRecordsBy_token_digestAtRecord () const throw (const rdm_exception&) {
    return Cursor_card_info (_GetRecordsByKeyAtRecord (TOKEN_DIGEST));
}

void Cursor_card_info::KeyFindBy_token_digest (const uint8_t token_digest_val[35]) const throw (const rdm_exception&) {
    _FindRecordsByKey(TOKEN_DIGEST, token_digest_val, sizeof(token_digest_val[0]) * 35);
}

void Cursor_card_info::SetFieldValues (const struct card_info &fields) const throw (const rdm_exception&) {
    Cursor::SetFieldValues (Type (), &fields);
}

void Cursor_card_info::GetFieldValues (struct card_info &fields) const throw (const rdm_exception&) {
    Cursor::GetFieldValues (Type (), &fields);
}

void Cursor_card_info::Set_access_rules_record_addr (const DB_ADDR &access_rules_record_addr_val) const throw (const rdm_exception&) {
    _SetField (ACCESS_RULES_RECORD_ADDR, &access_rules_record_addr_val);
}

void Cursor_card_info::Get_access_rules_record_addr (DB_ADDR &access_rules_record_addr_val) const throw (const rdm_exception&) {
    _GetField (ACCESS_RULES_RECORD_ADDR, &access_rules_record_addr_val);
}

void Cursor_card_info::Set_card_access_type (const uint8_t &card_access_type_val) const throw (const rdm_exception&) {
    _SetField (CARD_ACCESS_TYPE, &card_access_type_val);
}

void Cursor_card_info::Get_card_access_type (uint8_t &card_access_type_val) const throw (const rdm_exception&) {
    _GetField (CARD_ACCESS_TYPE, &card_access_type_val);
}

    void Cursor_card_info::Set_token_digest (const uint8_t token_digest_val[35]) const throw (const rdm_exception&) {
    _SetField (TOKEN_DIGEST, token_digest_val);
}

    void Cursor_card_info::Get_token_digest (uint8_t token_digest_val[35]) const throw (const rdm_exception&) {
    _GetField (TOKEN_DIGEST, token_digest_val);
}

    void Cursor_card_info::Set_last_digits (const char last_digits_val[4]) const throw (const rdm_exception&) {
    _SetField (LAST_DIGITS, last_digits_val);
}

    void Cursor_card_info::Get_last_digits (char last_digits_val[4]) const throw (const rdm_exception&) {
    _GetField (LAST_DIGITS, last_digits_val);
}

Cursor_card_info::~Cursor_card_info () {
}

recordType Cursor_card_access_rules::Type (void) {
    return CARD_ACCESS_RULES;
}

Cursor_card_access_rules::Cursor_card_access_rules (void) throw () {
}

Cursor_card_access_rules::Cursor_card_access_rules (const Cursor& cursor) throw (const rdm_exception&) : Cursor (cursor, Type ()) {
}

Cursor_card_access_rules::Cursor_card_access_rules (const Cursor_card_access_rules& cursor) throw () : Cursor (cursor) {
}

Cursor_card_access_rules& Cursor_card_access_rules::operator = (const Cursor& cursor) throw (const rdm_exception&) {
    return static_cast<Cursor_card_access_rules&>(_AssignAndVerifyType (Type (), cursor)); /*lint !e1772 ('*this' is being returned from the called function) */ /*lint !e1774 (_AssignAndVerifyType will make sure this is the right type, so static_check is sufficient) */
} /*lint !e1529 (checking for assignment to 'this' in the called function) */

Cursor_card_access_rules& Cursor_card_access_rules::operator = (const Cursor_card_access_rules& cursor) throw () {
    return static_cast<Cursor_card_access_rules&>(_AssignAndVerifyType (Type (), static_cast<const Cursor&>(cursor))); /*lint !e1772 ('*this' is being returned from the called function) */ /*lint !e1774 (AssignedAndVerifyType will make sure this is the right type, so static_check is sufficient) */
} /*lint !e1529 (checking for assignment to 'this' in the called function) */

void Cursor_card_access_rules::SetFieldValues (const struct card_access_rules &fields) const throw (const rdm_exception&) {
    Cursor::SetFieldValues (Type (), &fields);
}

void Cursor_card_access_rules::GetFieldValues (struct card_access_rules &fields) const throw (const rdm_exception&) {
    Cursor::GetFieldValues (Type (), &fields);
}

    void Cursor_card_access_rules::Set_access_data (const uint8_t access_data_val[500]) const throw (const rdm_exception&) {
    _SetField (ACCESS_DATA, access_data_val);
}

    void Cursor_card_access_rules::Get_access_data (uint8_t access_data_val[500]) const throw (const rdm_exception&) {
    _GetField (ACCESS_DATA, access_data_val);
}

Cursor_card_access_rules::~Cursor_card_access_rules () {
}

