//! \file

#ifndef Y_MKL_Fit_Assembly_Included
#define Y_MKL_Fit_Assembly_Included 1

#include "y/mkl/fit/type/entity.hpp"

namespace Yttrium
{
    namespace MKL
    {
        namespace Fit
        {

            class Assembly
            {
            public:
                explicit Assembly() noexcept;
                virtual ~Assembly() noexcept;


                void admit(const Entity &) noexcept;
                void clear() noexcept;

                const size_t maxNameSize; //!< max name size

            private:
                Y_Disable_Copy_And_Assign(Assembly);
                virtual void clear_() noexcept = 0;
            };

        }
    }

}

#endif // !Y_MKL_Fit_Assembly_Included

