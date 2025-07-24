#include "y/hashing/digest.hpp"
#include "y/utest/run.hpp"


using namespace Yttrium;

Y_UTEST(hashing_digest)
{

    Hashing::Digest d(3);

    std::cerr << d << std::endl;

}
Y_UDONE()

