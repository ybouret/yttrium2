
//! \file

#ifndef Y_MKL_ODE_ExplicitIntegrator_Included
#define Y_MKL_ODE_ExplicitIntegrator_Included 1

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
            //! Explicit Integrator
            //
            //
            //__________________________________________________________________
            template <typename T>
            class ExplicitIntegrator
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
                explicit ExplicitIntegrator();          //!< setup
                virtual ~ExplicitIntegrator() noexcept; //!< cleanup

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________

                //! best effort step
                /**
                 \param ystart in/out variables
                 \param x1 starting coordinate
                 \param x2 finish coordinate
                 \param h1 initial step
                 \param eq equation
                 \param cb optional callback
                 \param step explicit step to use
                 */
                void operator()(Writable<T> &    ystart,
                                const T          x1,
                                const T          x2,
                                const T          h1,
                                Equation &       eq,
                                Callback * const cb,
                                StepType   &     step);

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                T eps; //!< fractional tolerance

            private:
                class Code;
                Y_Disable_Copy_And_Assign(ExplicitIntegrator); //!< discarding
                Code * const code;                             //!< cleanup
            };
        }
    }

}

#endif // !Y_MKL_ODE_ExplicitIntegrator_Included

