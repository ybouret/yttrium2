
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
                Y_Disable_Copy_And_Assign(ExplicitDriver);
                Code * const code;
            };

        }

    }

}

#endif // !Y_MKL_ODE_ExplicitDriver_Included

