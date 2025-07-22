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

        //______________________________________________________________________
        //
        //
        //
        //! Zero Finding API
        //
        //
        //______________________________________________________________________
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
            inline explicit ZFind() noexcept {} //!< setup
            inline virtual ~ZFind() noexcept {} //!< cleanup

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual const char * callSign() const noexcept;


            //! lookup interface
            /**
             x.b and f.b are the result, and f.b must be the
             last evaluated call before return
             \param x initial bracketing x.a and x.c
             \param f initial function with f.a*f.c <=0
             \param F function to zero
             \return position of zero
             */
            virtual T lookup(Triplet<T> &x, Triplet<T> &f, FunctionType &F) = 0;


            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            
            //! wrapper to callable FUNCTION
            /**
             \param F any compatible function
             \param x initial bracketing x.a and x.c
             \param f initial function with f.a*f.c <=0
             \return position of zero
             */
            template <typename FUNCTION>   inline
            T operator()(FUNCTION &F, Triplet<T> &x, Triplet<T> &f )
            {
                Wrapper1D<T,T,FUNCTION> FW(F);
                return lookup(x,f,FW);
            }


            //! setup
            /**
             upon success, F is called
             \param hx handle for x
             \param hf handle for f
             \param x  triplet with x.a and x.c initialized
             \param f  triplet with f.a * f.c <= 0
             \param F  function to zero
             \return true if f.a or f.c was 0, x.b and f.b are set accordingly
             */
            bool found(Handle &hx, Handle &hf, Triplet<T> &x, Triplet<T> &f, FunctionType &F);




        private:
            Y_Disable_Copy_And_Assign(ZFind); //!< discarding
        };

    }
}

#endif

