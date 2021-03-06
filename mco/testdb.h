/* Generated by eXtremeDB Schema Compiler, build 1792, rev. stable, rev. 19776
 * at Sat Nov 19 20:51:21 2016
 */

#if defined(MCO_CPP_INTERFACE) && defined(__MCO__testdb__H__)
#error C API schema file testdb.h should not be included directly from C++ application
#endif
#ifndef __MCO__testdb__H__
#define __MCO__testdb__H__

#ifdef __cplusplus
extern "C" { 
#endif

#include "mco.h"
#include "mcouda.h"

#ifndef MCO_COMP_VER_MAJOR 
#define MCO_COMP_VER_MAJOR 7
#define MCO_COMP_VER_MINOR 0
#define MCO_COMP_BUILD_NUM 1792
#define MCO_COMP_REVISION "stable, rev. 19776"
#endif /*MCO_COMP_VER_MAJOR*/ 

#if !defined(MCO_MEMCPY_DEFINED) && !MCO_CFG_BUILTIN_MEMCPY
#define MCO_MEMCPY_DEFINED
void mco_memcpy(void* dest, const void* src, mco_size_t nbt);
#endif /*MCO_MEMCPY_DEFINED*/





/*---------------------------------------------------------------------*/
/* Dictionary                                                          */

mco_dictionary_h testdb_get_dictionary(void);

mco_calculator_h testdb_get_calculator(void);

#ifdef MCO_CPP_INTERFACE
namespace testdb
{
#endif


/*---------------------------------------------------------------------*/
/* Handles and Class Codes                                             */

#ifndef MCO_CPP_INTERFACE
typedef struct ListEntry_  { MCO_Hf h; }  ListEntry;
#else
class ListEntry;
#endif
#define                                   ListEntry_code   1


/*---------------------------------------------------------------------*/
/* Structures for fixed part of the structure                          */

typedef struct ListEntry_fixed_ {
  char salted_key[35];
  uint1 is_good;
  uint8 meta_info;
} ListEntry_fixed;



/*---------------------------------------------------------------------*/
/* class ListEntry methods                                             */

MCO_RET      ListEntry_new                                    ( mco_trans_h t, /*OUT*/ ListEntry *handle );
MCO_RET      ListEntry_delete                                 ( ListEntry *handle );
MCO_RET      ListEntry_set_allocation_block_size             (mco_trans_h t, mco_size_t block_size);
MCO_RET      ListEntry_set_caching_priority                  (mco_trans_h t, int priority);
MCO_RET      ListEntry_delete_all                             ( mco_trans_h t );
MCO_RET      ListEntry_checkpoint                             ( ListEntry *handle );

MCO_RET      ListEntry_salted_key_get                         ( ListEntry *handle, /*OUT*/ char * dest, uint2 dest_size);
MCO_RET      ListEntry_salted_key_put                         ( ListEntry *handle, const char * src, uint2 len) ;

MCO_RET      ListEntry_is_good_get                            ( ListEntry *handle, /*OUT*/ uint1 * result);
MCO_RET      ListEntry_is_good_put                            ( ListEntry *handle, uint1 value );

MCO_RET      ListEntry_meta_info_get                          ( ListEntry *handle, /*OUT*/ uint8 * result);
MCO_RET      ListEntry_meta_info_put                          ( ListEntry *handle, uint8 value );

MCO_RET      ListEntry_from_cursor                            ( mco_trans_h t, mco_cursor_h c, /*OUT*/ ListEntry *handle );

MCO_RET      ListEntry_by_salted_key_index_cursor             ( mco_trans_h t, /*OUT*/ mco_cursor_h c );
MCO_RET      ListEntry_by_salted_key_search                   ( mco_trans_h t, /*INOUT*/ mco_cursor_h c, MCO_OPCODE op_, const char *salted_key_key_, uint2 sizeof_salted_key_key_ );
MCO_RET      ListEntry_by_salted_key_compare                  ( mco_trans_h t, mco_cursor_h c, const char *salted_key_key_, uint2 sizeof_salted_key_key_, /*OUT*/ int *result_ );
MCO_RET      ListEntry_by_salted_key_pattern_size             ( const char *salted_key_key_, uint2 sizeof_salted_key_key_, /*OUT*/ uint4 *size_);
MCO_RET      ListEntry_by_salted_key_pattern_search           ( mco_trans_h t, mco_cursor_h c, /*INOUT*/ void *allocated_pattern, mco_size_t memsize , const char *salted_key_key_, uint2 sizeof_salted_key_key_ );
MCO_RET      ListEntry_by_salted_key_pattern_next             ( mco_trans_h t, mco_cursor_h c, /*INOUT*/ void *allocated_pattern );
MCO_RET      ListEntry_by_salted_key_locate                   ( mco_trans_h t, /*OUT*/ mco_cursor_h c, ListEntry * handle);
MCO_RET      ListEntry_by_salted_key_find                     ( mco_trans_h t, const char *salted_key_key_, uint2 sizeof_salted_key_key_, /*OUT*/ ListEntry *handle_);
MCO_RET      ListEntry_fixed_get                              ( ListEntry *handle_, ListEntry_fixed* dst_ );
MCO_RET      ListEntry_fixed_put                              ( ListEntry *handle_, ListEntry_fixed const* src_ );

#ifdef __cplusplus
#ifdef MCO_CPP_INTERFACE
} // namespace testdb
#endif
} // extern "C" 
#endif

#endif
