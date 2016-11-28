/* Generated by eXtremeDB Schema Compiler, build 1792, rev. stable, rev. 19776
 * at Sat Nov 19 20:51:21 2016
 */

#ifndef __MCO__testdb__HPP__
#define __MCO__testdb__HPP__

#include "mco.h"

#define MCO_CPP_INTERFACE
#include "testdb.h"

namespace testdb
{

class McoBase_
{
  protected:
  MCO_Hf h_;
  bool    valid_;
  McoBase_() : valid_(false) {} 
  McoBase_(McoBase_ const& other) : valid_(other.valid_) { mco_assign_handle(&h_, &other.h_); } 
  public:
  bool is_valid() const  { return valid_; }
  void set_valid(bool v) { valid_ = v; }
};






class ListEntry : public McoBase_
{
  public:

  MCO_RET create( mco_trans_h t );
  MCO_RET remove();
  MCO_RET set_allocation_block_size(mco_trans_h t, mco_size_t block_size);
  MCO_RET set_caching_priority(mco_trans_h t, int priority);
  MCO_RET remove_all( mco_trans_h t );
  MCO_RET checkpoint();
  MCO_RET salted_key_get(char * dest, uint2 dest_size);
  MCO_RET salted_key_put( const char * src, uint2 len );
  MCO_RET is_good_get( uint1 & result );
  MCO_RET is_good_put( uint1 value );
  MCO_RET meta_info_get( uint8 & result );
  MCO_RET meta_info_put( uint8 value );
  MCO_RET from_cursor( mco_trans_h t, mco_cursor_h c );

  class by_salted_key // b-tree index
  { public: 
    static MCO_RET cursor( mco_trans_h t, /*OUT*/ mco_cursor_h c );
    static MCO_RET search( mco_trans_h t_, mco_cursor_h c_, MCO_OPCODE op_, const char *salted_key_key_, uint2 sizeof_salted_key_key_ ); 
    static MCO_RET compare( mco_trans_h t_, mco_cursor_h c_, const char *salted_key_key_, uint2 sizeof_salted_key_key_, int & result_ ); 
    static MCO_RET pattern_size( const char *salted_key_key_, uint2 sizeof_salted_key_key_, /*OUT*/ uint4 *size_); 
    static MCO_RET pattern_search  ( mco_trans_h t, mco_cursor_h c, /*INOUT*/ void *allocated_pattern, mco_size_t memsize , const char *salted_key_key_, uint2 sizeof_salted_key_key_); 
    static MCO_RET pattern_next  ( mco_trans_h t, mco_cursor_h c, void *allocated_pattern ); 
    static MCO_RET locate(mco_trans_h t, /*OUT*/ mco_cursor_h c, ListEntry & handle);
    static MCO_RET find( mco_trans_h t_, const char *salted_key_key_, uint2 sizeof_salted_key_key_, /*OUT*/ ListEntry & handle_); 
  }; // by_salted_key
};

inline  MCO_RET ListEntry::create( mco_trans_h t )
{ MCO_RET ret_ = testdb::ListEntry_new(t,this); set_valid(ret_==MCO_S_OK); return ret_; 
}

inline  MCO_RET ListEntry::remove()
{ MCO_RET ret_; set_valid(false); return (ret_=testdb::ListEntry_delete(this)); 
}

inline  MCO_RET ListEntry::set_allocation_block_size(mco_trans_h t, mco_size_t block_size)
{ return testdb::ListEntry_set_allocation_block_size(t, block_size); 
}

inline  MCO_RET ListEntry::set_caching_priority(mco_trans_h t, int priority)
{ return testdb::ListEntry_set_caching_priority(t, priority); 
}

inline  MCO_RET ListEntry::remove_all( mco_trans_h t )
{ MCO_RET ret_; set_valid(false); return (ret_=testdb::ListEntry_delete_all(t)); 
}

inline  MCO_RET ListEntry::checkpoint()
{ MCO_RET ret_=testdb::ListEntry_checkpoint(this); return ret_;
}

inline  MCO_RET ListEntry::salted_key_get(char * dest, uint2 dest_size)
{ MCO_RET ret_ = testdb::ListEntry_salted_key_get(this,dest,dest_size); return ret_; 
}

inline  MCO_RET ListEntry::salted_key_put( const char * src, uint2 len )
{ MCO_RET ret_ = testdb::ListEntry_salted_key_put(this,src, len); return ret_; 
}

inline  MCO_RET ListEntry::is_good_get ( uint1 & result )
{ MCO_RET ret_ = testdb::ListEntry_is_good_get(this, &result); return ret_;
} 

inline  MCO_RET ListEntry::is_good_put( uint1 value )
{ MCO_RET ret_ = testdb::ListEntry_is_good_put(this, value); return ret_; 
} 

inline  MCO_RET ListEntry::meta_info_get ( uint8 & result )
{ MCO_RET ret_ = testdb::ListEntry_meta_info_get(this, &result); return ret_;
} 

inline  MCO_RET ListEntry::meta_info_put( uint8 value )
{ MCO_RET ret_ = testdb::ListEntry_meta_info_put(this, value); return ret_; 
} 

inline  MCO_RET ListEntry::from_cursor( mco_trans_h t, mco_cursor_h c )
{ MCO_RET ret_ = testdb::ListEntry_from_cursor(t,c,this); set_valid(ret_==MCO_S_OK); return ret_; 
}

inline  MCO_RET ListEntry::by_salted_key::cursor( mco_trans_h t, /*OUT*/ mco_cursor_h c )
{ return testdb::ListEntry_by_salted_key_index_cursor(t,c); 
}

inline  MCO_RET ListEntry::by_salted_key::search( mco_trans_h t_, mco_cursor_h c_, MCO_OPCODE op_, const char *salted_key_key_, uint2 sizeof_salted_key_key_ ) 
{ return testdb::ListEntry_by_salted_key_search(t_,c_,op_, salted_key_key_, sizeof_salted_key_key_); 
}

inline  MCO_RET ListEntry::by_salted_key::compare( mco_trans_h t_, mco_cursor_h c_, const char *salted_key_key_, uint2 sizeof_salted_key_key_, int & result_ ) 
{ return testdb::ListEntry_by_salted_key_compare(t_,c_, salted_key_key_, sizeof_salted_key_key_, &result_); 
}

inline  MCO_RET ListEntry::by_salted_key::pattern_size( const char *salted_key_key_, uint2 sizeof_salted_key_key_, /*OUT*/ uint4 *size_) 
{ return testdb::ListEntry_by_salted_key_pattern_size( salted_key_key_, sizeof_salted_key_key_, size_); 
}

inline  MCO_RET ListEntry::by_salted_key::pattern_search ( mco_trans_h t, mco_cursor_h c, void *allocated_pattern, mco_size_t memsize , const char *salted_key_key_, uint2 sizeof_salted_key_key_)
{ return testdb::ListEntry_by_salted_key_pattern_search (t,c, allocated_pattern, memsize, salted_key_key_, sizeof_salted_key_key_); 
}

inline  MCO_RET ListEntry::by_salted_key::pattern_next ( mco_trans_h t, mco_cursor_h c, void *allocated_pattern )
{ return testdb::ListEntry_by_salted_key_pattern_next (t, c, allocated_pattern); 
}

inline  MCO_RET ListEntry::by_salted_key::locate(mco_trans_h t, /*OUT*/ mco_cursor_h c, ListEntry & handle)
{ return testdb::ListEntry_by_salted_key_locate(t, c, &handle ); 
}

inline  MCO_RET ListEntry::by_salted_key::find( mco_trans_h t_, const char *salted_key_key_, uint2 sizeof_salted_key_key_, /*OUT*/ ListEntry & handle_) 
{ MCO_RET ret_ = testdb::ListEntry_by_salted_key_find(t_, salted_key_key_, sizeof_salted_key_key_, &handle_ ); handle_.set_valid(ret_==MCO_S_OK); return ret_; 
}




} // namespace testdb

#endif
