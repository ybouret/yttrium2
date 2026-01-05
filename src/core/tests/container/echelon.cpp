#include "y/container/ordered/ranked.hpp"
#include "y/utest/run.hpp"
#include "y/random/park-miller.hpp"

#include <cstring>

using namespace Yttrium;

Y_UTEST(ordered_echelon)
{
    Random::ParkMiller ran;
    int                data[20] = { 0 };
    const size_t       num = sizeof(data)/sizeof(data[0]);
    memset(data,0,sizeof(data));
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

    while( stk.size )
    {
        const int top = stk.pop();
        std::cerr << stk << " -> " << top << std::endl;
    }


    std::cerr << "updating..." << std::endl;
    for(size_t i=0;i<num;++i)
    {
        const int value = ran.to<uint8_t>();
        stk.push(value, Sign::Increasing<int> );
    }
    std::cerr << stk << std::endl;

    for(size_t i=0;i<num;++i)
    {
        for(size_t j=0;j<4;++j)
        {
            const int newValue =ran.to<uint8_t>();
            stk.update( & (stk.tree[i] = newValue), Sign::Increasing<int> );
            std::cerr
            << "@" << std::setw(4) << i  << ":"
            << std::setw(4) << newValue
            << " -> " << stk << std::endl;
        }
    }





}
Y_UDONE()

