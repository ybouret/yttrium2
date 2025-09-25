
//! \file

#ifndef Y_MKL_ODE_ExplicitStep_Included
#define Y_MKL_ODE_ExplicitStep_Included 1

#include "y/mkl/ode/field.hpp"
#include "y/ability/identifiable.hpp"

namespace Yttrium
{
    namespace MKL
    {
        namespace ODE
        {
            template <typename T>
            class ExplicitStep : public Identifiable
            {
            public:
                typedef Field<T>  FieldType;
                typedef typename  FieldType::Equation Equation;
                typedef typename  FieldType::Callback Callback;



                virtual void operator()(Writable<T> &       yout,
                                        Writable<T> &       yerr,
                                        const Readable<T> & y,
                                        const Readable<T> & dydx,
                                        const T             x,
                                        const T             h,
                                        Equation          & f,
                                        Callback * const    cb) = 0;

                virtual ~ExplicitStep() noexcept;

            protected:
                explicit ExplicitStep() noexcept;

            private:
                Y_Disable_Copy_And_Assign(ExplicitStep);
            };
        }

    }

}

#endif // !Y_MKL_ODE_ExplicitStep_Included
