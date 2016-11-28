#include "saltedkey.hpp"
#include <iostream>
#include <cassert>
#include <cstring> 

#define BASE_64_ARRAY_SZ (64 + 1) 
#define CARD_ALPHABET \
             "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"

////////////////////////////////////////////////////////////////////////////////

// Put in a separately linked module - as an extern C function perhaps
void rand_key(unsigned int seed, char key[SALTED_KEY_SZ])
{
    assert(key != nullptr);

    /* LCG */
    static char base64[BASE_64_ARRAY_SZ] = CARD_ALPHABET;
    const unsigned a = 1103515245, c = 12345, m = 1 << 31;
    for (unsigned i = 0; i < (SALTED_KEY_SZ - 1); ++i) {
        unsigned idx = ((seed = (seed * a + c) % m) >> 20) % 64;
        assert(0 <= idx && idx < 64);
        key[i] = base64[idx];
        // cout << "key = " << key[i] << ", value = " << (int)key[i] << std::endl;
    }
}

////////////////////////////////////////////////////////////////////////////////

SaltedKey::SaltedKey(unsigned min, unsigned max) : rand_(min, max) 
{ 
}

////////////////////////////////////////////////////////////////////////////////

void SaltedKey::gen_key_(const unsigned seed)
{
    rand_key(seed, key_);
    assert(strlen(key_) == (SALTED_KEY_SZ - 1));
}

////////////////////////////////////////////////////////////////////////////////

// warning: this is not thread safe as sharing this object instance between
// threads can result in inconsistent results - creata a new instance for
// each thread.
const char * SaltedKey::key()
{
    const unsigned seed = rand_.draw();
    gen_key_(seed);
    return key_;
}

////////////////////////////////////////////////////////////////////////////////

const char * SaltedKey::key(const unsigned seed)
{
    gen_key_(seed);
    return key_;
}

////////////////////////////////////////////////////////////////////////////////

void SaltedKey::key(const char * const k) 
{ 
    assert(strlen(k) < sizeof(key_)); 
    strcpy(key_, k); 
}

////////////////////////////////////////////////////////////////////////////////

void SaltedKey::key(const std::string& k) 
{ 
    assert(k.length() < sizeof(key_)); 
    strcpy(key_, k.c_str()); 
}

