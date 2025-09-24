
//! \file

#ifndef Y_MKL_ODE_RK4_Included
#define Y_MKL_ODE_RK4_Included 1

#include "y/mkl/ode/field.hpp"

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
            //! Runge-Kutta-4
            //
            //
            //__________________________________________________________________
            template <typename T>
            class RK4
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                typedef typename Field<T>::Equation Equation; //!< alias
                typedef typename Field<T>::Callback Callback; //!< alias

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                explicit RK4(const size_t nmax=0); //!< setup \param nmax optional max dimensions
                virtual ~RK4() noexcept;           //!< cleanup

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________

                //! evaluate next vector
                /**
                 \param yout output vector
                 \param y    input  vector
                 \param dydx input derivatives
                 \param x    initial position
                 \param h    required step
                 \param f    equation
                 \param cb   optional vector callback
                 */
                void operator()(Writable<T> &       yout,
                                const Readable<T> & y,
                                const Readable<T> & dydx,
                                const T             x,
                                const T             h,
                                Equation &          f,
                                Callback * const    cb=0);

            private:
                class Code;
                Y_Disable_Copy_And_Assign(RK4); //!< disable
                Code * const code;              //!< inner code
            };
        }
    }

}



#endif // !Y_MKL_ODE_RK4_Included
