
//! \file

#ifndef Y_Ink_Blur_Hook_Included
#define Y_Ink_Blur_Hook_Included 1

#include "y/ink/blur/data.hpp"
#include "y/ink/blur/function.hpp"


namespace Yttrium
{
    namespace Ink
    {
        //______________________________________________________________________
        //
        //
        //
        //! Prepare data according to function
        //
        //
        //______________________________________________________________________
        template <typename T>
        class BlurHook : public BlurData<T>
        {
        public:

            //! prepare data \param F blur function
            inline explicit BlurHook(const BlurFunction<T> &F) :
            BlurData<T>(F,F.rmax())
            {
            }

            //! cleanup
            inline virtual ~BlurHook() noexcept
            {
            }


        private:
            Y_Disable_Copy_And_Assign(BlurHook); //!< discarding
        };

    }

}

#endif // !Y_Ink_Blur_Hook_Included
