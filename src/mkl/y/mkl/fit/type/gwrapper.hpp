
//! \file

#ifndef Y_Fit_GWrapper_Included
#define Y_Fit_GWrapper_Included 1

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
            //! Regular Gradient to Adjustable::Gradient
            //
            //
            //__________________________________________________________________
            template <typename GRADIENT, typename ABSCISSA,typename ORDINATE>
            class GWrapper : public Y_Fit_Gradient
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
                //! setup \param g persistent compatible gradient(dFda,x,vars,aorg)
                inline explicit GWrapper(GRADIENT &g) :
                Y_Fit_Gradient(this, & GWrapper:: compute ),
                G(g)
                {
                }

#if defined(_MSC_VER)
#pragma warning (pop)
#endif

                //! cleanup
                inline virtual ~GWrapper() noexcept {}

            private:
                Y_Disable_Copy_And_Assign(GWrapper); //!< discarding
                GRADIENT &G;                         //!< callable function

                //! interfacing
                /**
                 \param dFda local gradient
                 \param x abscissae
                 \param i index
                 \param vars variables
                 \param aorg current values
                 \param used flags of used values
                 \return F(x[i],vars,aorg)
                 */
                ORDINATE compute(Writable<ORDINATE>       &dFda,
                                 const Readable<ABSCISSA> &x,
                                 const size_t              i,
                                 const Variables &         vars,
                                 const Readable<ORDINATE> &aorg,
                                 const Readable<bool>     &used)
                {
                    return G(dFda,x[i],vars,aorg,used);
                }

            };
        }

    }

}

#endif // !Y_Fit_GWrapper_Included

