

//! \file

#ifndef Y_Ink_Draw_Circle_Included
#define Y_Ink_Draw_Circle_Included

#include "y/ink/draw/putpixel.hpp"

namespace Yttrium
{

    namespace Ink
    {

        namespace Draw
        {

            template <typename IMAGE, typename PUTPIXEL> inline
            void SetPixel(IMAGE &img, const unit_t x, const unit_t y, PUTPIXEL &putPixel)
            {
                if( img.containsAbscissa(x) && img.containsOrdinate(y) )
                    putPixel(x,y);
            }


            //! draw a circle
            /**
             \param img pixmap, Area based
             \param xm  circle x-center
             \param ym  circle y-center
             \param r   circle radius
             \param putPixel putPixel(x,y)
             */
            template <typename IMAGE, typename PUTPIXEL> inline
            void Circle_(IMAGE &       img,
                         const unit_t  xm,
                         const unit_t  ym,
                         unit_t        r,
                         PUTPIXEL    & putPixel)
            {
                assert(r>=0);
                unit_t x = -r, y = 0, err = 2-2*r; /* II. Quadrant */
                do {
#if 0
                    putPixel(xm-x, ym+y); /*   I. Quadrant */
                    putPixel(xm-y, ym-x); /*  II. Quadrant */
                    putPixel(xm+x, ym-y); /* III. Quadrant */
                    putPixel(xm+y, ym+x); /*  IV. Quadrant */
#endif // 0
                    SetPixel(img,xm-x, ym+y,putPixel);
                    SetPixel(img,xm-y, ym-x,putPixel);
                    SetPixel(img,xm+x, ym-y,putPixel);
                    SetPixel(img,xm+y, ym+x,putPixel);
                    r = err;
                    if (r <= y) err += ++y*2+1;           /* e_xy+e_y < 0 */
                    if (r > x || err > y) err += ++x*2+1; /* e_xy+e_x > 0 or no 2nd y-step */
                } while (x < 0);
            }

            template <typename IMAGE, typename PUTPIXEL> inline
            void Circle(IMAGE &       img,
                        const unit_t  xm,
                        const unit_t  ym,
                        unit_t        r,
                        PUTPIXEL    & putPixel)
            {
                PutPixel1<PUTPIXEL,IMAGE> wrapper =  { putPixel, img };
                Circle_(img,xm,ym,r,wrapper);
            }

            template <typename IMAGE, typename PUTPIXEL, typename ARG2> inline
            void Circle(IMAGE &       img,
                        const unit_t  xm,
                        const unit_t  ym,
                        unit_t        r,
                        PUTPIXEL    & putPixel,
                        ARG2        & arg2)
            {
                PutPixel2<PUTPIXEL,IMAGE,ARG2> wrapper =  { putPixel, img, arg2 };
                Circle_(img,xm,ym,r,wrapper);
            }

            
        }

    }

}

#endif // !Y_Ink_Draw_Circle_Included

