
#include "y/apex/k/parcel/api.hpp"
#include <iostream>


namespace Yttrium
{
    namespace Apex
    {


        const char * const ParcelAPI:: HumanReadablePlan[Metrics::Plans] =
        {
            "Plan8 ", "Plan16", "Plan32", "Plan64"
        };
        
        bool ParcelAPI:: sanity() const noexcept
        {
            Y_Apex_Parcel_Check(size<=maxi);
            return check();
        }

        size_t ParcelAPI:: update(ParcelAPI * const sync[]) noexcept
        {
            assert(sync);
            adjust(); assert( sanity() );
            return Propagate(sync,bits());
        }
    }

}

