
//! \file

#ifndef Y_MKL_ODE_Example_Included
#define Y_MKL_ODE_Example_Included 1

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
            //! differential equation for Exponential
            //
            //
            //__________________________________________________________________
            template <typename T>
            class dExponential
            {
            public:
                typedef typename ODE::Field<T>::Equation Equation; //!< alias

                //! setup \param kValue coefficient
                inline dExponential(const T kValue) :
                k(kValue),
                f(this, & dExponential<T>::compute )
                {
                }

                //! cleanup
                inline ~dExponential() noexcept
                {
                }


                const T  k; //!< coefficient
                Equation f; //!< equation

            private:
                Y_Disable_Copy_And_Assign(dExponential); //!< discard

                //! compute derivatives
                /**
                 \param dydx result
                 \param y    position
                 */
                inline void compute(Writable<T> &      dydx,
                                    const              T,
                                    const Readable<T> &y)
                {
                    assert(1==dydx.size());
                    assert(1==y.size());
                    dydx[1] = k * y[1];
                }
            };


            //__________________________________________________________________
            //
            //
            //
            //! differential equation for Spring
            //
            //
            //__________________________________________________________________
            template <typename T>
            class dSpring
            {
            public:
                typedef typename ODE::Field<T>::Equation Equation; //!< alias

                //! setup \param kValue coefficient
                inline dSpring(const T pulsation,
                               const T viscosity) :
                omega(pulsation),
                lambda(viscosity),
                f(this, & dSpring<T>::compute )
                {
                }

                //! cleanup
                inline ~dSpring() noexcept
                {
                }


                const T  omega;  //!< coefficient
                const T  lambda; //!< viscosity
                Equation f;      //!< equation

            private:
                Y_Disable_Copy_And_Assign(dSpring); //!< discard

                //! compute derivatives
                /**
                 \param dydx result
                 \param y    position
                 */
                inline void compute(Writable<T> &      dydx,
                                    const              T,
                                    const Readable<T> &y)
                {
                    assert(2==dydx.size());
                    assert(2==y.size());
                    dydx[1] = y[2];
                    dydx[2] = - omega * omega * y[1] - lambda * y[2];
                }
            };
        }

    }

}


#endif // !Y_MKL_ODE_Example_Included

