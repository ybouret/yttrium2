
//! \file

#ifndef Y_MKL_ODE_RK4_Included
#define Y_MKL_ODE_RK4_Included 1

#include "y/mkl/ode/field.hpp"

namespace Yttrium
{
    namespace MKL
    {
        namespace ODE
        {
            template <typename T>
            class RK4
            {
            public:
                typedef typename Field<T>::Equation DiffEq;

                explicit RK4(const size_t nmax=0);
                virtual ~RK4() noexcept;

                void operator()(Writable<T> &       yout,
                                const Readable<T> & y,
                                const Readable<T> & dydx,
                                const T             x,
                                const T             h,
                                DiffEq &            f);

            private:
                class Code;
                Y_Disable_Copy_And_Assign(RK4);
                Code * const code;
            };
        }
    }

}



#endif // !Y_MKL_ODE_RK4_Included
