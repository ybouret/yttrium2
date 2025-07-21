
//! \file

#ifndef Y_MKL_Bracket_Included
#define Y_MKL_Bracket_Included 1

#include "y/mkl/triplet.hpp"
#include "y/mkl/function-wrapper-1d.hpp"

namespace Yttrium
{
    namespace MKL
    {

        template <typename T>
        struct Bracket
        {
            typedef Function<T,T> FunctionType; //!< alias

            //!
            /**
             - start with x.a,f.a and x.c,f.c
             */
            static bool Inside(Triplet<T> &x, Triplet<T> &f, FunctionType &F);

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


