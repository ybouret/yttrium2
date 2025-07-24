#include "y/hashing/digest.hpp"
#include "y/hashing/to.hpp"
#include "y/utest/run.hpp"

#include "y/hashing/crc32.hpp"
#include "y/format/hexadecimal.hpp"


using namespace Yttrium;

Y_UTEST(hashing_digest)
{

    Hashing::Digest d = "abc";

    std::cerr << d << std::endl;

    Hashing::CRC32 crc32;
    const uint32_t hash = Hashing::To<uint32_t>(crc32,"Hello World!");
    std::cerr << Hexadecimal(hash) << std::endl;
    Hashing::Digest D = "67fcdacc";
    std::cerr << D << std::endl;

}
Y_UDONE()

