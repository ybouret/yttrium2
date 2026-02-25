
//! \file

#ifndef Y_Ink_Blur_Metrics_Included
#define Y_Ink_Blur_Metrics_Included 1

#include "y/core/setup.hpp"

namespace Yttrium
{
    namespace Ink
    {
        //______________________________________________________________________
        //
        //
        //
        //! Radius of blur, computing number of points inside
        //
        //
        //______________________________________________________________________
        class BlurMetrics
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit BlurMetrics(const unit_t rmax); //!< setup \param rmax radius
            virtual ~BlurMetrics()         noexcept; //!< cleanup

            //__________________________________________________________________
            //
            //
            // methods
            //
            //__________________________________________________________________
            size_t count() const; //!< \return number of points less than |r|

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            const unit_t r;  //!< radius
            const unit_t r2; //!< r^2

        private:
            Y_Disable_Copy_And_Assign(BlurMetrics); //!< discarding
        };

    }

}

#endif // !Y_Ink_Blur_Metrics_Included

