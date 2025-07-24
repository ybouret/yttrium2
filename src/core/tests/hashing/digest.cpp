#include "y/hashing/md.hpp"
#include "y/hashing/to.hpp"
#include "y/utest/run.hpp"

#include "y/hashing/crc32.hpp"
#include "y/format/hexadecimal.hpp"


using namespace Yttrium;

Y_UTEST(hashing_digest)
{

    Hashing::Digest d = "abc";

    std::cerr << d << std::endl;

    static const char msg[] = "Hello World!";
    Hashing::CRC32 crc32;
    const uint32_t hash = Hashing::To<uint32_t>(crc32,msg);
    std::cerr << Hexadecimal(hash) << std::endl;
    Hashing::Digest D = "67fcdacc";
    std::cerr << D << std::endl;
    Hashing::Digest D2 = Hashing::MD::Of(crc32,msg);
    std::cerr << D2 << std::endl;
}
Y_UDONE()

