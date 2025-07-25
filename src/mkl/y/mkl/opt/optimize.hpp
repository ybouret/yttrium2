
//! \file

#ifndef Y_MKL_Optimize_Included
#define Y_MKL_Optimize_Included 1

#include "y/mkl/triplet.hpp"
#include "y/mkl/function-wrapper-1d.hpp"

namespace Yttrium
{
    namespace MKL
    {

        //! Optimize API
        template <typename T>
        struct Optimize
        {
            typedef Function<T,T> FunctionType; //!< alias

            //! run steps up to convergence
            /**
             - the result is f.b at x.b
             - f.b = F(x.b) is called before return
             \param x initial ordered positions
             \param f initial local minimum
             \param F function to minimize
             \return minimum location
             */
            static T Run(Triplet<T> &   x,
                         Triplet<T> &   f,
                         FunctionType & F);

            //! wrapper
            /**
             \param F compatible function
             \param x initial ordered positions
             \param f initial local minimum
             \return minimum location
             */
            template <typename FUNCTION> static inline
            T Run(FUNCTION &F, Triplet<T> &x, Triplet<T> &f)
            {
                Wrapper1D<T,T,FUNCTION> FW(F);
                return Run(x,f,FW);
            }
        };

    }

}

#endif
