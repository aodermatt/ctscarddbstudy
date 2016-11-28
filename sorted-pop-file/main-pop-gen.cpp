#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include <saltedkey.hpp>
#include <cassert>

// limit - 20M or whatever - specify size 
// gen salted key text file - write to ofstream text file
// pipe to sort ? 
// 
int main(int argc, char * argv[])
{
    if (argc == 1) {
        std::cout << "provide filename\n";
        return -1;
    }

    std::string filename(argv[1]);
    std::ofstream outfile(filename.c_str());

    assert(argc == 3);
    unsigned max = atoi(argv[2]);

    if (!outfile) {
        std::cout << "file does not exist " << filename << std::endl;
        return -1;
    }

    SaltedKey sk(0, max - 1);
    for (unsigned i = 0; i < max; ++i) {
        sk.gen_key(i);
        const char * s = sk.key(); 
        outfile << s << std::endl;
    }

    // next I use the Linux sort program with
    // sort this-argv1-filename -o sorted-file and then input this sorted file
    // into the main-pop-gen.cpp as main-pop-gen sorted-file and hardcode
    // sorted filename or shift up the markers file as argument status.

    return 0;
}


