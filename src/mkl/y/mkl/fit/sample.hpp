//! \file

#ifndef Y_Fit_Sample_Included
#define Y_Fit_Sample_Included 1

#include "y/container/writable.hpp"
#include "y/string.hpp"

namespace Yttrium
{
    namespace MKL
    {

        template <
        typename ORDINATE,
        typename ABSCISSA
        >
        class Sample
        {
        public:


            const String name;
        private:
            Y_Disable_Copy_And_Assign(Sample);
        };

    }
}


#endif // !Y_Fit_Sample_Included

