
//! \file

#ifndef Y_Ink_Blur_Function_Included
#define Y_Ink_Blur_Function_Included 1

#include "y/ability/identifiable.hpp"

namespace Yttrium
{
    namespace Ink
    {
        template <typename T> class BlurFunction : public Identifiable
        {
        public:
            inline explicit BlurFunction() noexcept : one(1) {}
            inline virtual ~BlurFunction() noexcept {}

            virtual T operator()(const unit_t r2) const = 0;

            inline const BlurFunction & blurFunction() const noexcept { return *this; }

            inline unit_t rmax() const
            {
                const T       Dmax = 256;
                const T       Vmin = one/Dmax;
                const BlurFunction &F  = *this;
                const T       f0 = F(0);
                for(unit_t r=1;;++r)
                {
                    const T f = F(r*r);
                    if(f/f0<=Vmin)
                        return --r;
                }
            }

            const T one; //!< 1

        private:
            Y_Disable_Copy_And_Assign(BlurFunction);
        };
    }

}

#endif // !Y_Ink_Blur_Function_Included
