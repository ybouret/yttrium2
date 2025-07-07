
#include "y/apex/k/parcel/api.hpp"
#include <iostream>


namespace Yttrium
{
    namespace Apex
    {

        bool ParcelAPI:: sanity() const noexcept
        {
            Y_Apex_Parcel_Check(size<=maxi);
            return check();
        }
    }

}

