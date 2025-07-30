#include "y/hashing/md.hpp"
#include "y/hashing/to.hpp"
#include "y/utest/run.hpp"

#include "y/hashing/crc32.hpp"
#include "y/format/hexadecimal.hpp"


using namespace Yttrium;

Y_UTEST(hashing_digest)
{

    Hashing::Digest d = "abc";

    Hexadecimal::Display(std::cerr, &d[1], d.size() ) << std::endl;
    std::cerr << d << std::endl;


    
}
Y_UDONE()

