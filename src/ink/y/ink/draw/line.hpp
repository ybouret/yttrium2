
//! \file

#ifndef Y_Ink_Draw_Line_Included
#define Y_Ink_Draw_Line_Included

#include "y/ink/pixmap.hpp"
#include "y/ink/draw/putpixel.hpp"
#include "y/ink/draw/clip.hpp"

namespace Yttrium
{

    namespace Ink
    {

        namespace Draw
        {
            template <typename T> inline
            T AbsOf(const T x) {
                return x < 0 ? -x : x;
            }

            template <typename PUTPIXEL> inline
            void Line_(unit_t       x0,
                       unit_t       y0,
                       const unit_t x1,
                       const unit_t y1,
                       PUTPIXEL &   putPixel)
            {
                const unit_t dx  =  AbsOf(x1-x0), sx = (x0<x1) ? 1 : -1;
                const unit_t dy  = -AbsOf(y1-y0), sy = (y0<y1) ? 1 : -1;
                unit_t       err = dx+dy; /* error value e_xy */

                for(;;){  /* loop */
                    putPixel(x0,y0);
                    if (x0==x1 && y0==y1) break;
                    const unit_t e2 = 2*err;
                    if (e2 >= dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */
                    if (e2 <= dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */
                }
            }

            template <typename PUTPIXEL, typename ARG1> inline
            void Line_(const unit_t x0,
                       const unit_t y0,
                       const unit_t x1,
                       const unit_t y1,
                       PUTPIXEL &   putPixel,
                       ARG1     &   arg1)
            {
                PutPixel1<PUTPIXEL,ARG1> wrapper = { putPixel, arg1 };
                Line_(x0,y0,x1,y1,wrapper);
            }

            template <typename PUTPIXEL, typename ARG1, typename ARG2> inline
            void Line_(const unit_t x0,
                       const unit_t y0,
                       const unit_t x1,
                       const unit_t y1,
                       PUTPIXEL &   putPixel,
                       ARG1     &   arg1,
                       ARG2     &   arg2)
            {
                PutPixel2<PUTPIXEL,ARG1,ARG2> wrapper = { putPixel, arg1, arg2 };
                Line_(x0,y0,x1,y1,wrapper);
            }

            template <typename PUTPIXEL, typename ARG1, typename ARG2, typename ARG3> inline
            void Line_(const unit_t x0,
                       const unit_t y0,
                       const unit_t x1,
                       const unit_t y1,
                       PUTPIXEL &   putPixel,
                       ARG1     &   arg1,
                       ARG2     &   arg2,
                       ARG3     &   arg3)
            {
                PutPixel3<PUTPIXEL,ARG1,ARG2,ARG3> wrapper = { putPixel, arg1, arg2, arg3 };
                Line_(x0,y0,x1,y1,wrapper);
            }

        }
    }

}


#endif // !Y_Ink_Draw_Line_Included
