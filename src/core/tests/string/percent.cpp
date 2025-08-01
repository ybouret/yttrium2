
#include "y/string/percent.hpp"
#include "y/utest/run.hpp"
#include "y/random/park-miller.hpp"
#include "y/calculus/bits-for.hpp"

using namespace Yttrium;

Y_UTEST(string_percent)
{

    Random::ParkMiller ran;

    std::cerr << StringPercent::Get(0,0) << std::endl;

    for(size_t iter=0;iter<10;++iter)
    {
        const size_t denom = ran.to<size_t>(4+ran.leq(10));
        const size_t dbits = BitsFor(denom);
        size_t       numer = ran.to<size_t>( ran.in<size_t>(0,dbits) );
        while(numer>denom)
        {
            numer = ran.to<size_t>( ran.in<size_t>(0,dbits) );
        }

        std::cerr << std::setw(6) << numer << " / " << std::setw(6) << denom << " => [" << StringPercent::Get(numer,denom) << "]" << std::endl;
    }
    
    std::cerr << StringPercent::Get(101,101) << std::endl;


}
Y_UDONE()
