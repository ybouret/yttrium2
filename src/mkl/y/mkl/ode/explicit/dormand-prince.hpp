
//! \file

#ifndef Y_MKL_ODE_DormandPrince_Included
#define Y_MKL_ODE_DormandPrince_Included 1

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
            //! Cash-Karp step
            //
            //
            //__________________________________________________________________
            template <typename T>
            class DormandPrince : public ExplicitStep<T>
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitioms
                //
                //______________________________________________________________
                typedef Field<T>  FieldType;                    //!< alias
                typedef typename  FieldType::Equation Equation; //!< alias
                typedef typename  FieldType::Callback Callback; //!< alias

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
                explicit DormandPrince();          //!< setup
                virtual ~DormandPrince() noexcept; //!< cleanup

                //______________________________________________________________
                //
                //
                // Interface
                //
                //______________________________________________________________
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
                Y_Disable_Copy_And_Assign(DormandPrince); //!< discard
                Code * const code;                        //!< inner algorithm
            };
        }

    }
}


#endif // !Y_MKL_ODE_DormandPrince_Included

