
#include "y/random/fill.hpp"

#include "y/random/park-miller.hpp"
#include "y/utest/run.hpp"
#include "y/container/sequence/vector.hpp"

using namespace Yttrium;


namespace {



}


Y_UTEST(random_fill)
{
    Random::ParkMiller ran;

    uint32_t dw = 0;
    for(size_t i=0;i<10;++i)
    {
        Random::Fill::Variable(ran,dw);
        std::cerr << dw << std::endl;
    }


}
Y_UDONE()
