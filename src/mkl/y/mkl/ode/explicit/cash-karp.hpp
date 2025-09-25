//! \file

#ifndef Y_MKL_ODE_CashKarp_Included
#define Y_MKL_ODE_CashKarp_Included 1

#include "y/mkl/ode/explicit/step.hpp"

namespace Yttrium
{
    namespace MKL
    {
        namespace ODE
        {

            template <typename T>
            class CashKarp : public ExplicitStep<T>
            {
            public:
                typedef Field<T>  FieldType;
                typedef typename  FieldType::Equation Equation;
                typedef typename  FieldType::Callback Callback;

                explicit CashKarp();
                virtual ~CashKarp() noexcept;

                virtual void operator()(Writable<T> &       yout,
                                        Writable<T> &       yerr,
                                        const Readable<T> & y,
                                        const Readable<T> & dydx,
                                        const T             x,
                                        const T             h,
                                        Equation          & f,
                                        Callback * const    cb);

                virtual const char *callSign() const noexcept;
                
            private:
                class Code;
                Y_Disable_Copy_And_Assign(CashKarp);
                Code * const code;
            };
        }

    }
}


#endif // !Y_MKL_ODE_CashKarp_Included

