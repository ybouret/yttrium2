
//! \file

#ifndef Y_Ink_Draw_PutPixel_Included
#define Y_Ink_Draw_PutPixel_Included

#include "y/ink/pixmap.hpp"

namespace Yttrium
{

    namespace Ink
    {

        //! wrapper for 1-argument putpixel
        template <typename PUTPIXEL, typename ARG1>
        struct PutPixel1
        {
            PUTPIXEL & proc; //!< reference
            ARG1     & arg1; //!< reference

            //! proc(x,y,arg1) \param x x \param y y
            inline void operator()(const unit_t x, const unit_t y)
            {
                proc(x,y,arg1);
            }
        };


        //! wrapper for 2-arguments putpixel
        template <typename PUTPIXEL, typename ARG1, typename ARG2>
        struct PutPixel2
        {
            PUTPIXEL & proc; //!< reference
            ARG1     & arg1; //!< reference
            ARG2     & arg2; //!< reference

            //! proc(x,y,arg1,arg2) \param x x \param y y
            inline void operator()(const unit_t x, const unit_t y)
            {
                proc(x,y,arg1,arg2);
            }
        };

        //! wrapper for 3-arguments putpixel
        template <typename PUTPIXEL, typename ARG1, typename ARG2, typename ARG3>
        struct PutPixel3
        {
            PUTPIXEL & proc; //!< reference
            ARG1     & arg1; //!< reference
            ARG2     & arg2; //!< reference
            ARG3     & arg3; //!< reference

            //! proc(x,y,arg1,arg2,arg3) \param x x \param y y
            inline void operator()(const unit_t x, const unit_t y)
            {
                proc(x,y,arg1,arg2,arg3);
            }
        };

    }

}

#endif // !Y_Ink_Draw_PutPixel_Included

