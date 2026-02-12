
//! \file

#ifndef Y_Ink_Draw_PutPixel_Included
#define Y_Ink_Draw_PutPixel_Included

#include "y/ink/pixmap.hpp"

namespace Yttrium
{

    namespace Ink
    {

        template <typename PUTPIXEL, typename ARG1>
        struct PutPixel1
        {
            PUTPIXEL & proc;
            ARG1     & arg1;

            inline void operator()(const unit_t x, const unit_t y)
            {
                proc(x,y,arg1);
            }
        };


        template <typename PUTPIXEL, typename ARG1, typename ARG2>
        struct PutPixel2
        {
            PUTPIXEL & proc;
            ARG1     & arg1;
            ARG2     & arg2;

            inline void operator()(const unit_t x, const unit_t y)
            {
                proc(x,y,arg1,arg2);
            }
        };

        template <typename PUTPIXEL, typename ARG1, typename ARG2, typename ARG3>
        struct PutPixel3
        {
            PUTPIXEL & proc;
            ARG1     & arg1;
            ARG2     & arg2;
            ARG3     & arg3;

            inline void operator()(const unit_t x, const unit_t y)
            {
                proc(x,y,arg1,arg2,arg3);
            }
        };

    }

}

#endif // !Y_Ink_Draw_PutPixel_Included

