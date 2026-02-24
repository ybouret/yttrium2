
//! \file

#ifndef Y_Ink_Blur_Metrics_Included
#define Y_Ink_Blur_Metrics_Included 1

#include "y/core/setup.hpp"

namespace Yttrium
{
    namespace Ink
    {
        class BlurMetrics
        {
        public:
            explicit BlurMetrics(const unit_t rmax);
            virtual ~BlurMetrics() noexcept;

            size_t count() const;

            const unit_t r;
            const unit_t r2;

        private:
            Y_Disable_Copy_And_Assign(BlurMetrics);
        };

    }

}

#endif // !Y_Ink_Blur_Metrics_Included

