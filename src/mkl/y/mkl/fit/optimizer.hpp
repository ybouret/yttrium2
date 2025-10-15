
//! \file

#ifndef Y_Fit_Optimizer_Included
#define Y_Fit_Optimizer_Included 1

#include "y/mkl/fit/adjustable.hpp"

namespace Yttrium
{
    namespace MKL
    {
        namespace Fit
        {
            template <typename ORDINATE>
            class Optimizer
            {
            public:
                explicit Optimizer();
                virtual ~Optimizer() noexcept;

            private:
                class Code;
                Y_Disable_Copy_And_Assign(Optimizer); //!< discarding
                Code * const code;                    //!< inner code
            };

        }

    }

}

#endif // !Y_Fit_Optimizer_Included

