
//! \file

#ifndef Y_Ink_Blur_Gauss_Included
#define Y_Ink_Blur_Gauss_Included 1

#include "y/ink/blur/function.hpp"
#include <cmath>


namespace Yttrium
{
    namespace Ink
    {

        class GaussBlurCommon
        {
        public:
            static const char * const CallSign;
            explicit GaussBlurCommon() noexcept;
            virtual ~GaussBlurCommon() noexcept;

        private:
            Y_Disable_Copy_And_Assign(GaussBlurCommon);
        };


        template <typename T>
        class GaussBlur : public GaussBlurCommon, public BlurFunction<T>
        {
        public:
            inline explicit GaussBlur(const T stddev) :
            sig( stddev ),
            sig2( sig*sig ),
            denom( sig2+sig2 )
            {

            }

            inline virtual ~GaussBlur() noexcept {}

            virtual const char * callSign() const noexcept { return CallSign; }

            virtual T operator()(const unit_t r2) const
            {
                const T u2 = (T)r2;
                const T arg = u2 / denom;
                return exp(-arg);
            }

            const T sig;
            const T sig2;
            const T denom;

        private:
            Y_Disable_Copy_And_Assign(GaussBlur);
        };

    }

}

#endif // !Y_Ink_Blur_Gauss_Included
