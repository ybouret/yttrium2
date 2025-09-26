
//! \file

#ifndef Y_MKL_ODE_ExplicitIntegrator_Included
#define Y_MKL_ODE_ExplicitIntegrator_Included 1

#include "y/mkl/ode/explicit/driver.hpp"

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
                typedef ExplicitDriver<T>             DriverType;
                
                explicit ExplicitIntegrator();
                virtual ~ExplicitIntegrator() noexcept;


            private:
                class Code;
                Y_Disable_Copy_And_Assign(ExplicitIntegrator);
                Code * const code;
            };
        }
    }

}

#endif // !Y_MKL_ODE_ExplicitIntegrator_Included

