
//! \file

#ifndef Y_Fit_FWrapper_Included
#define Y_Fit_FWrapper_Included 1

#include "y/mkl/fit/type/defs.hpp"

namespace Yttrium
{
    namespace MKL
    {
        namespace Fit
        {

            //__________________________________________________________________
            //
            //
            //
            //! Regular Function to Adjustable::Function
            //
            //
            //__________________________________________________________________
            template <typename FUNCTION, typename ABSCISSA,typename ORDINATE>
            class FWrapper : public Y_Fit_Function
            {
            public:
                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable : 4355 )
#endif
                //! setup \param f persistent compatible function(x,vars,aorg)
                inline explicit FWrapper(FUNCTION &f) :
                Y_Fit_Function(this, & FWrapper:: compute ),
                F(f)
                {
                }

#if defined(_MSC_VER)
#pragma warning (pop)
#endif

                //! cleanup
                inline virtual ~FWrapper() noexcept {}

            private:
                Y_Disable_Copy_And_Assign(FWrapper); //!< discarding
                FUNCTION &F;                         //!< callable function

                //! interfacing
                /**
                 \param x abscissae
                 \param i index
                 \param vars variables
                 \param aorg current values
                 \return F(x[i],vars,aorg)
                 */
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

