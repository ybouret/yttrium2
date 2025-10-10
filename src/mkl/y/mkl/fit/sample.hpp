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
            typename ABSCISSA,
            typename ORDINATE
            >
            class Sample : public Entity
            {
            public:

                template <typename UID> inline
                explicit Sample(const UID                & id,
                                const Readable<ABSCISSA> & _X,
                                const Readable<ORDINATE> & _Y,
                                Writable<ORDINATE>       & _Z):
                Entity(id), X(_X), Y(_Y), Z(_Z)
                {
                }

                inline virtual ~Sample() noexcept {}

                const Readable<ABSCISSA> & X;
                const Readable<ABSCISSA> & Y;
                Writable<ABSCISSA>       & Z;

            private:
                Y_Disable_Copy_And_Assign(Sample);
            };
        }
        
    }
}


#endif // !Y_Fit_Sample_Included

