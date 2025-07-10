

#include "y/format/human-readable.hpp"
#include "y/random/park-miller.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(format_human_readable)
{

    Random::ParkMiller ran;
    for(unsigned bits=0;bits<=64;++bits)
    {
        const uint64_t u = ran.to<uint64_t>(bits);
        std::cerr << HumanReadable(u) << std::endl;
    }


}
Y_UDONE()
