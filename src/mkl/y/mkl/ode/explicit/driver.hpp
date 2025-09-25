
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

            template <typename T>
            class ExplicitDriver
            {
            public:
                typedef Field<T>                      FieldType;
                typedef typename  FieldType::Equation Equation;
                typedef typename  FieldType::Callback Callback;
                typedef ExplicitStep<T>               StepType;

                explicit ExplicitDriver();
                virtual ~ExplicitDriver() noexcept;

            private:
                class Code;
                Y_Disable_Copy_And_Assign(ExplicitDriver);
                Code * const code;
            };

        }

    }

}

#endif // !Y_MKL_ODE_ExplicitDriver_Included

