
//! \file

#ifndef Y_MKL_ODE_CashKarp_Included
#define Y_MKL_ODE_CashKarp_Included 1

#include "y/mkl/ode/field.hpp"

namespace Yttrium
{
    namespace MKL
    {
        namespace ODE
        {
            template <typename T>
            class CashKarp
            {
            public:
                explicit CashKarp();
                virtual ~CashKarp() noexcept;

            private:
                class Code;
                Y_Disable_Copy_And_Assign(CashKarp);
                Code * const code;
            };
        }

    }
}


#endif // !Y_MKL_ODE_CashKarp_Included

