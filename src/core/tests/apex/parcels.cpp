
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
    static inline void testParcels(Random::Bits &ran)
    {
        uint64_t            arr[4];
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
                const Apex::Parcels target(source);
                std::cerr << target << std::endl;
                Y_ASSERT(source.plan==target.plan);
                Y_ASSERT(source.api->length() == target.api->length());
                Y_ASSERT(0 == memcmp(source.api->ro(),target.api->ro(),source.api->length()) );
            }

            source.set(Apex::Plan32);
            std::cerr << source << std::endl;
            {
                const Apex::Parcels target(source);
                std::cerr << target << std::endl;
                Y_ASSERT(source.plan==target.plan);
                Y_ASSERT(source.api->length() == target.api->length());
                Y_ASSERT(0 == memcmp(source.api->ro(),target.api->ro(),source.api->length()) );
            }
            source.set(Apex::Plan64); Y_ASSERT(0==memcmp(source.api->ro(),arr,sizeof(arr)));


            source.set(Apex::Plan16);
            std::cerr << source << std::endl;
            {
                const Apex::Parcels target(source);
                std::cerr << target << std::endl;
                Y_ASSERT(source.plan==target.plan);
                Y_ASSERT(source.api->length() == target.api->length());
                Y_ASSERT(0 == memcmp(source.api->ro(),target.api->ro(),source.api->length()) );
            }
            source.set(Apex::Plan64); Y_ASSERT(0==memcmp(source.api->ro(),arr,sizeof(arr)));

            source.set(Apex::Plan8);
            std::cerr << source << std::endl;
            {
                const Apex::Parcels target(source);
                std::cerr << target << std::endl;
                Y_ASSERT(source.plan==target.plan);
                Y_ASSERT(source.api->length() == target.api->length());
                Y_ASSERT(0 == memcmp(source.api->ro(),target.api->ro(),source.api->length()) );
            }
            source.set(Apex::Plan64); Y_ASSERT(0==memcmp(source.api->ro(),arr,sizeof(arr)));

            std::cerr << "all-shuffle" << std::endl;
            for(size_t i=0;i<100;++i)
            {
                source.set(Apex::PlanType(ran.leq(3)));
            }
            source.set(Apex::Plan64); Y_ASSERT(0==memcmp(source.api->ro(),arr,sizeof(arr)));
        }
    }
}

Y_UTEST(apex_parcels)
{
    Random::ParkMiller  ran;
    Apex::Parcels::SetExchangePolicy( Apex::ExchangeNeutralEndian );
    testParcels(ran);

    Apex::Parcels::SetExchangePolicy( Apex::ExchangeBuiltInEndian);
    testParcels(ran);


}
Y_UDONE()
