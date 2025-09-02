
//! \file

#ifndef Y_MKL_Minimize_Included
#define Y_MKL_Minimize_Included 1

#include "y/mkl/triplet.hpp"
#include "y/mkl/function-wrapper-1d.hpp"

namespace Yttrium
{
    namespace MKL
    {

        //______________________________________________________________________
        //
        //
        //! minimizing commmon parts
        //
        //______________________________________________________________________
        struct Minimizing
        {
            static const char  * const CallSign; //!< "Minimize"

            //! bracketing method
            enum How
            {
                Inside, //!< bracket inside original range
                Direct, //!< no bracketing, already at local minimum
                Expand  //!< expand from original direction
            };
            
        };

        //______________________________________________________________________
        //
        //
        //
        //! Minimize API
        //
        //
        //______________________________________________________________________
        template <typename T>
        struct Minimize
        {
            typedef Function<T,T> FunctionType; //!< alias

            //! run steps up to convergence
            /**
             - the result is f.b at x.b
             - f.b = F(x.b) is called before return
             \param how bracketing methof
             \param x   initial ordered positions
             \param f   initial local minimum
             \param F   function to minimize
             \return minimum location
             */
            static T Run(const Minimizing::How how,
                         Triplet<T> &          x,
                         Triplet<T> &          f,
                         FunctionType &        F);

            //! wrapper
            /**
             \param how bracketing methof
             \param F   compatible function
             \param x   initial ordered positions
             \param f   initial local minimum
             \return minimum location
             */
            template <typename FUNCTION> static inline
            T Run(const Minimizing::How how, FUNCTION &F, Triplet<T> &x, Triplet<T> &f)
            {
                Wrapper1D<T,T,FUNCTION> FW(F);
                return Run(how,x,f,FW);
            }
        };

    }

}


#endif

