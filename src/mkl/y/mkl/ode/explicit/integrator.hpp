
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
            template <typename T>
            class ExplicitIntegrator
            {
            public:
                typedef Field<T>                      FieldType;
                typedef typename  FieldType::Equation Equation;
                typedef typename  FieldType::Callback Callback;
                typedef ExplicitStep<T>               StepType;

                explicit ExplicitIntegrator();
                virtual ~ExplicitIntegrator() noexcept;

                void operator()(Writable<T> &    ystart,
                                const T          x1,
                                const T          x2,
                                const T          h1,
                                Equation &       eq,
                                Callback * const cb,
                                StepType   &     step);

                T eps;
            private:
                class Code;
                Y_Disable_Copy_And_Assign(ExplicitIntegrator);
                Code * const code;
            };
        }
    }

}

#endif // !Y_MKL_ODE_ExplicitIntegrator_Included

