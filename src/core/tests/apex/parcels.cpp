
#include "y/apex/k/parcels.hpp"
#include "y/apex/m/archon.hpp"


#include "y/utest/run.hpp"
#include "y/random/park-miller.hpp"
#include "y/random/fill.hpp"
#include "y/check/static.hpp"
#include <cstring>

using namespace Yttrium;


Y_UTEST(apex_parcels)
{
    Random::ParkMiller  ran;
    uint64_t            arr[2];
    static const size_t num = sizeof(arr)/sizeof(arr[0]);
    static const size_t maxBits = sizeof(arr) * 8;
    for(size_t numBits=0;numBits<=maxBits;++numBits)
    {
        Y_Memory_BZero(arr);
        Random::Fill::Block64(ran,arr,numBits);

        Apex::Parcels source(sizeof(arr),Apex::Plan64);  Y_ASSERT(source.api->maxi>=num);
        memcpy( source.api->rw(), arr, (source.api->size=num)*sizeof(uint64_t) );
        const size_t bits = source.update();
        Y_ASSERT(bits==numBits);
        std::cerr << source << std::endl;
        {
            const Apex::Parcels p(source);
            std::cerr << p << std::endl;
        }
    }

}
Y_UDONE()
