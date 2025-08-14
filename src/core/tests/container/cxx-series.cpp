

#include "y/container/cxx/series.hpp"
#include "y/utest/run.hpp"
#include "y/apex/rational.hpp"
#include "y/random/park-miller.hpp"

using namespace Yttrium;


Y_UTEST(container_cxx_series)
{
    Random::ParkMiller ran;

    {
        CxxSeries<int> arr(10);
        for(size_t i=1;i<=arr.capacity();++i)
        {
            arr << ran.in<int>(-10,10);
        }
        std::cerr << arr << std::endl;
    }

    {
        CxxSeries<apq> arr(8);
        for(size_t i=1;i<=arr.capacity();++i)
        {
            arr << apq(ran,ran.leq<size_t>(10),1+ran.leq<size_t>(10));
        }
        std::cerr << arr << std::endl;
    }

}
Y_UDONE()

