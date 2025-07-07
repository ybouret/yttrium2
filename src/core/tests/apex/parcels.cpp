
#include "y/apex/k/parcels.hpp"

#include "y/apex/m/archon.hpp"


#include "y/utest/run.hpp"
#include "y/random/park-miller.hpp"
#include "y/random/fill.hpp"
#include "y/check/static.hpp"
#include <cstring>

using namespace Yttrium;

namespace
{
    template <typename T>
    static inline void testParcel(const Apex::Parcel<T> &p, const size_t numBits)
    {
        std::cerr << "\t" << p << std::endl;
        Y_ASSERT( p.bits() == numBits );
    }



}

Y_UTEST(apex_parcels)
{

}
Y_UDONE()
