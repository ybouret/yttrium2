
//! \file

#ifndef Y_MKL_Bracket_Included
#define Y_MKL_Bracket_Included 1

#include "y/mkl/triplet.hpp"
#include "y/mkl/function-wrapper-1d.hpp"

namespace Yttrium
{
    namespace MKL
    {

        //______________________________________________________________________
        //
        //
        //
        //! Bracketing of minimum
        //
        //
        //______________________________________________________________________
        template <typename T>
        struct Bracket
        {
            typedef Function<T,T> FunctionType; //!< alias

            //!
            /**
             - start with x.a,f.a and x.c,f.c
             \param x initial interval [x.a:x.c]
             \param f initial values   [f.a:f.c]
             \param F function to evaluate
             \return true if local min, false of global min
             */
            static bool Inside(Triplet<T> &x, Triplet<T> &f, FunctionType &F);

            //! wrapper
            /**
             \param F compatible function
             \param x initial interval [x.a:x.c]
             \param f initial values   [f.a:f.c]
             \return true if local min, false of global min
             */
            template <typename FUNCTION> static inline
            bool Inside(FUNCTION &F, Triplet<T> &x, Triplet<T> &f)
            {
                Wrapper1D<T,T,FUNCTION> FW(F);
                return Inside(x,f,FW);
            }

        };


    }

}


#endif


