
//! \file

#ifndef Y_MKL_ODE_Example_Included
#define Y_MKL_ODE_Example_Included 1

#include "y/mkl/ode/field.hpp"

namespace Yttrium
{
    namespace MKL
    {
        namespace ODE
        {

            template <typename T>
            class dExponential
            {
            public:
                typedef typename ODE::Field<T>::Equation DiffEq;

                inline dExponential(const T kValue) :
                k(kValue),
                f(this, & dExponential<T>::compute )
                {
                }

                inline ~dExponential() noexcept
                {
                }


                const T  k;
                DiffEq   f;

            private:
                Y_Disable_Copy_And_Assign(dExponential);
                inline void compute(Writable<T> & dydx, const T, const Readable<T> &y)
                {
                    assert(1==dydx.size());
                    assert(1==y.size());
                    dydx[1] = k * y[1];
                }
            };

        }

    }

}


#endif // !Y_MKL_ODE_Example_Included

