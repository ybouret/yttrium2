
#include "y/apex/k/parcel/api.hpp"
#include <iostream>


namespace Yttrium
{
    namespace Apex
    {


        const char * const ParcelAPI:: HumanReadablePlan[Metrics::Views] =
        {
            "Plan8 ", "Plan16", "Plan32", "Plan64"
        };
        
        bool ParcelAPI:: sanity() const noexcept
        {
            Y_Apex_Parcel_Check(size<=maxi);
            return check();
        }
    }

}

