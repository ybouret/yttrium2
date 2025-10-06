//! \file

#ifndef Y_Chemical_Weasel_DiffusionCoefficientsTable_Included
#define Y_Chemical_Weasel_DiffusionCoefficientsTable_Included 1

#include "y/chemical/weasel.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        class Weasel:: DiffusionCoefficientsTable
        {
        public:
            explicit DiffusionCoefficientsTable();
            virtual ~DiffusionCoefficientsTable() noexcept;



        private:
            Y_Disable_Copy_And_Assign(DiffusionCoefficientsTable);
        };
    }
}

#endif // !Y_Chemical_Weasel_DiffusionCoefficientsTable_Included

