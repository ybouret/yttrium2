
//! \file

#ifndef Y_MKL_ODE_Example_Included
#define Y_MKL_ODE_Example_Included 1

#include "y/mkl/ode/field.hpp"
#include "y/mkl/v2d.hpp"

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



            //__________________________________________________________________
            //
            //
            //
            //! differential equation for Astra
            //
            //
            //__________________________________________________________________
            template <typename T>
            class dAstra : public ODE::Field<T>::Equation
            {
            public:
                typedef typename ODE::Field<T>::Equation Equation; //!< alias


                inline explicit dAstra(const V2D<T> &position, const T pulsation) :
                Equation(this, & dAstra<T>::compute ),
                r0(position),
                v0(r0.ortho()),
                radius(r0.norm()),
                omega(pulsation),
                omega2(omega*omega),
                speed(radius*omega)
                {
                    Coerce(v0) /= v0.norm();
                    Coerce(v0) *= speed;
                }


                inline virtual ~dAstra() noexcept {}

                inline void init(Writable<T> &y)
                {
                    y[1] = r0.x; y[2] = r0.y;
                    y[3] = v0.x; y[4] = v0.y;
                }

                const V2D<T> r0;
                const V2D<T> v0;
                const T      radius;
                const T      omega;
                const T      omega2;
                const T      speed;

            private:
                Y_Disable_Copy_And_Assign(dAstra);

                inline void compute(Writable<T> &      dydt,
                                    const              T,
                                    const Readable<T> &y)
                {
                    const V2D<T> r( y[1], y[2] );
                    const V2D<T> v( y[3], y[4] );
                    dydt[1] = v.x;
                    dydt[2] = v.y;
                    dydt[3] = -omega2 * r.x;
                    dydt[4] = -omega2 * r.y;
                }
            };
        }

    }
}


#endif // !Y_MKL_ODE_Example_Included

