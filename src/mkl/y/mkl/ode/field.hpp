//! \file

#ifndef Y_MKL_ODE_Field_Included
#define Y_MKL_ODE_Field_Included 1

#include "y/container/writable.hpp"
#include "y/functor.hpp"

namespace Yttrium
{
    namespace MKL
    {
        namespace ODE
        {

            //__________________________________________________________________
            //
            //
            //
            //! Definitions
            //
            //
            //__________________________________________________________________
            template <typename T>
            struct Field
            {

                typedef Functor<void,TL3(Writable<T> &,T,const Readable<T>)> Equation; //!< alias
                typedef Functor<void,TL2(Writable<T> &,T)>                   Callback; //!< alias

                //! evaluate with pre-callback
                /**
                 \param eq   equation
                 \param dydx output derivatives
                 \param x    input position
                 \param y    input variables, checked by cb
                 \param cb   optional callback
                 */
                static inline
                void Compute(Equation &          eq,
                             Writable<T> &       dydx,
                             const T             x,
                             Writable<T> &       y,
                             Callback * const    cb)
                {
                    if(cb) (*cb)(y,x);
                    eq(dydx,x,y);
                }

            };

        }
    }

}


#endif // !Y_MKL_ODE_Field_Included
