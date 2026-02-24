
//! \file

#ifndef Y_Ink_Blur_Hook_Included
#define Y_Ink_Blur_Hook_Included 1

#include "y/ink/blur/data.hpp"
#include "y/ink/blur/function.hpp"


namespace Yttrium
{
    namespace Ink
    {
        template <typename T>
        class BlurHook : public BlurData<T>
        {
        public:
            inline explicit BlurHook(const BlurFunction<T> &F) :
            BlurData<T>(F,F.rmax())
            {
            }

            inline virtual ~BlurHook() noexcept
            {
            }


        private:
            Y_Disable_Copy_And_Assign(BlurHook);
        };

    }

}

#endif // !Y_Ink_Blur_Hook_Included
