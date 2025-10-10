//! \file

#ifndef Y_Fit_Sample_Included
#define Y_Fit_Sample_Included 1

#include "y/container/writable.hpp"
#include "y/mkl/fit/entity.hpp"

namespace Yttrium
{
    namespace MKL
    {
        namespace Fit
        {
            template <
            typename ORDINATE,
            typename ABSCISSA
            >
            class Sample : public Entity
            {
            public:

                template <typename UID> inline
                explicit Sample(const UID &uid) :
                Entity(uid)
                {
                }

                inline virtual ~Sample() noexcept {}

            private:
                Y_Disable_Copy_And_Assign(Sample);
            };
        }
        
    }
}


#endif // !Y_Fit_Sample_Included

