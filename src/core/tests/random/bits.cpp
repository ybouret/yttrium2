#include "y/random/park-miller.hpp"
#include "y/system/seed.hpp"
#include "y/utest/run.hpp"
#include "y/hexadecimal.hpp"

using namespace Yttrium;

Y_UTEST(random_bits)
{
    for(size_t i=0;i<8;++i)
    {
        std::cerr << "Seed: " << System::Seed::Get<uint16_t>() << std::endl;
    }

    Random::ParkMiller ran;
    for(size_t i=0;i<10;++i)
    {
        std::cerr << Hexadecimal( ran.next32() ) << std::endl;
    }
}
Y_UDONE()

