
//! \file

#ifndef Y_Ink_Blur_Function_Included
#define Y_Ink_Blur_Function_Included 1

#include "y/ability/identifiable.hpp"

namespace Yttrium
{
    namespace Ink
    {
        //______________________________________________________________________
        //
        //
        //
        //! Blur function prototype
        //
        //
        //______________________________________________________________________
        template <typename T> class BlurFunction : public Identifiable
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            inline explicit BlurFunction() noexcept : one(1) {} //!< setup
            inline virtual ~BlurFunction() noexcept {}          //!< cleanup

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual T operator()(const unit_t r2) const = 0; //!< \param r2 x^2+y^2 \return value at r2

            //! helper for constructors \return *this
            inline const BlurFunction & blurFunction() const noexcept { return *this; }

            //! \return radius with weight below 1/256
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

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const T one; //!< 1

        private:
            Y_Disable_Copy_And_Assign(BlurFunction); //!< discarding
        };
    }

}

#endif // !Y_Ink_Blur_Function_Included
