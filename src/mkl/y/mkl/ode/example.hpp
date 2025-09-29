
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
            class dExponential : public ODE::Field<T>::Equation
            {
            public:
                typedef typename ODE::Field<T>::Equation Equation; //!< alias

                //! setup \param kValue coefficient
                inline dExponential(const T kValue) :
                Equation(this, & dExponential<T>::compute ),
                k(kValue)
                {
                }

                //! cleanup
                inline virtual ~dExponential() noexcept
                {
                }


                const T  k; //!< coefficient

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
            class dSpring : public ODE::Field<T>::Equation
            {
            public:
                typedef typename ODE::Field<T>::Equation Equation; //!< alias

                //! setup \param pulsation pulsation \param viscosity viscosity
                inline dSpring(const T pulsation,
                               const T viscosity) :
                Equation(this, & dSpring<T>::compute ),
                omega(pulsation),
                lambda(viscosity)
                {
                }

                //! cleanup
                inline virtual ~dSpring() noexcept
                {
                }


                const T  omega;  //!< coefficient
                const T  lambda; //!< viscosity

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

