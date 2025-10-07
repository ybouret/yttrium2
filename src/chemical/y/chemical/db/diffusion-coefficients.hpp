
//! \file

#ifndef Y_Chemical_DiffusionCoefficientsTable_Included
#define Y_Chemical_DiffusionCoefficientsTable_Included 1


#include "y/core/setup.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        //! encoded table of diffusion coefficients in water
        struct DiffusionCoefficients
        {
            static const double SI;       //!< unit is 10^-9 m^s/s
            static const char   JSDict[]; //!< JSON Dictionary
            static const size_t Length;   //!< number of entries
        };
    }

}

#endif // !Y_Chemical_DiffusionCoefficientsTable_Included

