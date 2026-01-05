#include "y/container/ordered/ranked.hpp"
#include "y/utest/run.hpp"
#include "y/random/park-miller.hpp"

using namespace Yttrium;

Y_UTEST(ordered_echelon)
{
    Random::ParkMiller ran;
    int                data[10] = { 0 };
    const size_t       num = sizeof(data)/sizeof(data[0]);
    Ranked<int>        stk(data,num);


    std::cerr << stk << std::endl;
    for(size_t i=0;i<num;++i)
    {
        const int value = ran.to<uint8_t>();
        stk.push(value, Sign::Increasing<int> );
        std::cerr << stk << std::endl;
    }

    stk.free();
    std::cerr << stk << std::endl;
    for(size_t i=0;i<num;++i)
    {
        const int value = ran.to<uint8_t>();
        stk.push(value, Sign::Decreasing<int> );
        std::cerr << stk << std::endl;
    }




}
Y_UDONE()

