//! \file

#ifndef Y_Chemical_Weasel_DiffusionCoefficientsTable_Included
#define Y_Chemical_Weasel_DiffusionCoefficientsTable_Included 1

#include "y/chemical/weasel.hpp"
#include "y/container/associative/hash/map.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        typedef HashMap<String,double> DiffusionCoefficientsDB; //!< alias

        //! decoded table of diffusion coefficients
        class Weasel:: DiffusionCoefficientsTable :
        public DiffusionCoefficientsDB
        {
        public:
            explicit DiffusionCoefficientsTable();          //!< decode
            virtual ~DiffusionCoefficientsTable() noexcept; //!< cleanup

        private:
            Y_Disable_Copy_And_Assign(DiffusionCoefficientsTable); //!< discarding
        };
    }
}

#endif // !Y_Chemical_Weasel_DiffusionCoefficientsTable_Included

