//! \file

#ifndef Y_MKL_ZFind_Included
#define Y_MKL_ZFind_Included 1

#include "y/mkl/function-wrapper-1d.hpp"
#include "y/mkl/triplet.hpp"
#include "y/ability/identifiable.hpp"

namespace Yttrium
{
    namespace MKL
    {

        template <typename T>
        class ZFind : public Identifiable
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            typedef Function<T,T> FunctionType; //!< alias

            //! helper to locate negative/positive end
            struct  Handle {
                T *neg; //!< pointer to negative end
                T *pos; //!< pointer to positive end
            };

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            inline explicit ZFind() noexcept {}
            inline virtual ~ZFind() noexcept {}

            //__________________________________________________________________
            //
            //
            // interface
            //
            //__________________________________________________________________
            virtual const char * callSign() const noexcept;

            //! setup
            /**
             \param hx handle for x
             \param hf handle for f
             \param x  triplet with x.a and x.c initialized
             \param f  triplat with f.a * f.c <= 0
             */
            bool found(Handle &hx, Handle &hf, Triplet<T> &x, Triplet<T> &f, FunctionType &F);

            template <typename FUNCTION> inline
            bool found(FUNCTION &F, Handle &hx, Handle &hf, Triplet<T> &x, Triplet<T> &f)
            {
                Wrapper1D<T,T,FUNCTION> WF(F);
                return found(hx,hf,x,f,WF);
            }




        private:
            Y_Disable_Copy_And_Assign(ZFind);
        };

    }
}

#endif

