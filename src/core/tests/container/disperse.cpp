
#include "y/container/algorithm/disperse.hpp"
#include "y/utest/run.hpp"

#include "y/container/sequence/vector.hpp"
#include "y/container/cxx/series.hpp"
#include "y/sorting/heap.hpp"
#include "y/core/utils.hpp"
#include "y/exception.hpp"

#include <cmath>

using namespace Yttrium;

namespace Yttrium
{
   

    static inline double scalarDistance(const double a, const double b) noexcept
    {
        return fabs(a-b);
    }

}

#include "y/random/park-miller.hpp"
#include "y/ascii/convert.hpp"

Y_UTEST(container_disperse)
{
    Random::ParkMiller ran;
    const size_t   n = argc>1 ? ASCII::Convert::To<size_t>(argv[1]) : 3;
    Vector<size_t> idx(n,0);
    Vector<double> pos(n,0);
    for(size_t i=n;i>0;--i)
    {
        pos[i] = ran.symm<double>();
    }

    std::cerr << "pos=" << pos << std::endl;

    Algo::Disperse::Make( TypeToType<double>(), idx,scalarDistance,pos);



}
Y_UDONE()

