
//! \file

#ifndef Y_Chemical_DiffusionCoefficientsTable_Included
#define Y_Chemical_DiffusionCoefficientsTable_Included 1


#include "y/core/setup.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        struct DiffusionCoefficients
        {
            static const double SI; //!< 10^-9 m^s/s
            static const char   JSDict[];
            static const size_t Length;
        };
    }

}

#endif // !Y_Chemical_DiffusionCoefficientsTable_Included

