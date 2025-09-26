
//! \file

#ifndef Y_MKL_ODE_ExplicitStep_Included
#define Y_MKL_ODE_ExplicitStep_Included 1

#include "y/mkl/ode/field.hpp"
#include "y/ability/identifiable.hpp"

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
            //! Explicit 4/5 step
            //
            //
            //__________________________________________________________________
            template <typename T>
            class ExplicitStep : public Identifiable
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                typedef Field<T>                      FieldType; //!< alias
                typedef typename  FieldType::Equation Equation;  //!< alias
                typedef typename  FieldType::Callback Callback;  //!< alias


                //______________________________________________________________
                //
                //
                // Interface
                //
                //______________________________________________________________

                //! take a step
                /**
                 \param yout output value
                 \param yerr error estimate
                 \param y    starting point
                 \param dydx starting derivative
                 \param x    starting coordinate
                 \param h    required step
                 \param eq   equation
                 \param cb   optional callback
                 */
                virtual void operator()(Writable<T> &       yout,
                                        Writable<T> &       yerr,
                                        const Readable<T> & y,
                                        const Readable<T> & dydx,
                                        const T             x,
                                        const T             h,
                                        Equation          & eq,
                                        Callback * const    cb) = 0;

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
                virtual ~ExplicitStep() noexcept; //!< cleanup

            protected:
                explicit ExplicitStep() noexcept; //!< setup

            private:
                Y_Disable_Copy_And_Assign(ExplicitStep); //!< discarding
            };
        }

    }

}

#endif // !Y_MKL_ODE_ExplicitStep_Included
