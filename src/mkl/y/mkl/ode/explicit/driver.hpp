
//! \file

#ifndef Y_MKL_ODE_ExplicitDriver_Included
#define Y_MKL_ODE_ExplicitDriver_Included 1

#include "y/mkl/ode/explicit/step.hpp"

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
            //! Explicit Step Driver
            //
            //
            //__________________________________________________________________
            template <typename T>
            class ExplicitDriver
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
                typedef ExplicitStep<T>               StepType;  //!< alias

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
                explicit ExplicitDriver();          //!< setup
                virtual ~ExplicitDriver() noexcept; //!< cleanup

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________

                //! take a controlled step
                /**
                 \param step  explicit step
                 \param y     in/out variables
                 \param x     in/out coordinate
                 \param dydx  original derivatives
                 \param yscal scaling for error computation
                 \param htry  trial step
                 \param hdid  performed step, hdid <= htry
                 \param hnext estimated next step
                 \param eps   fractional accuracy
                 \param eq    equation
                 \param cb    optional callback
                 */
                void operator()(StepType          & step,
                                Writable<T>       & y,
                                T                 & x,
                                const Readable<T> & dydx,
                                const Readable<T> & yscal,
                                const T             htry,
                                T                 & hdid,
                                T                 & hnext,
                                const T             eps,
                                Equation &          eq,
                                Callback * const    cb);

            private:
                class Code;
                Y_Disable_Copy_And_Assign(ExplicitDriver); //!< discarding
                Code * const code;  //!< inner algorithm
            };

        }

    }

}

#endif // !Y_MKL_ODE_ExplicitDriver_Included

