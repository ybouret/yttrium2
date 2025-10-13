
//! \file

#ifndef Y_Fit_FWrapper_Included
#define Y_Fit_FWrapper_Included 1

#include "y/mkl/fit/defs.hpp"

namespace Yttrium
{
    namespace MKL
    {
        namespace Fit
        {

            template <typename FUNCTION, typename ABSCISSA,typename ORDINATE>
            class FWrapper : public Y_Fit_Functor
            {
            public:
#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable : 4355 )
#endif
                inline explicit FWrapper(FUNCTION &f) :
                Y_Fit_Functor(this, & FWrapper:: compute ),
                F(f)
                {
                }

#if defined(_MSC_VER)
#pragma warning (pop)
#endif
                inline virtual ~FWrapper() noexcept {}

            private:
                Y_Disable_Copy_And_Assign(FWrapper);
                FUNCTION &F;

                ORDINATE compute(const Readable<ABSCISSA> &x,
                                 const size_t              i,
                                 const Variables &         vars,
                                 const Readable<ORDINATE> &aorg)
                {
                    return F(x[i],vars,aorg);
                }

            };
        }

    }

}

#endif // !Y_Fit_FWrapper_Included

