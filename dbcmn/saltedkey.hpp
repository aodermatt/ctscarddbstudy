#ifndef  SALTEDKEY_HPP
#define  SALTEDKEY_HPP

#include <string>
#include <random>

#ifndef SALTED_KEY_SZ
#define SALTED_KEY_SZ (35 + 1)      // add +1 for null terminator
#endif

void rand_key(unsigned int seed, char key[SALTED_KEY_SZ]);

class Random 
{
public:
    Random(const unsigned min, const unsigned max) : min_(min), max_(max) {}
    Random(std::mt19937::result_type seed) : eng(seed) {}

    unsigned draw(void) {
        return std::uniform_int_distribution<unsigned>{min_, max_}(eng); 
    }

private:        
    std::mt19937 eng{std::random_device{}()};
    unsigned min_, max_;
};

////////////////////////////////////////////////////////////////////////////////

class SaltedKey
{
public: 
    SaltedKey(unsigned min, unsigned max);

    // use random number generated to establish seed.
    const char * key();          

    // seed used is passed in and controlled by the client interface
    const char * key(const unsigned seed);

    // stuff in your own key - only used for generating keys for sorted input.
    void key(const char * const k);
    void key(const std::string& k);

    // get the key string.
    const char * key() const { return key_; }
    operator const char * () { return key_; }

private:
    void gen_key_(const unsigned seed);
    Random rand_;
    char key_[SALTED_KEY_SZ] = {0};
};


#endif // SALTEDKEY_HPP


