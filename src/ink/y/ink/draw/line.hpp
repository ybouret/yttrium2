
//! \file

#ifndef Y_Ink_Draw_Line_Included
#define Y_Ink_Draw_Line_Included

#include "y/ink/draw/putpixel.hpp"
#include "y/calculus/iabs.hpp"

namespace Yttrium
{

    namespace Ink
    {

        namespace Draw
        {
            

            //! no-arg line drawing
            /**
             \param x0 initial x
             \param y0 initial y
             \param x1 final x
             \param y1 final y
             \param putPixel putPixel(x,y) on each line point
             */
            template <typename PUTPIXEL> inline
            void Line_(unit_t       x0,
                       unit_t       y0,
                       const unit_t x1,
                       const unit_t y1,
                       PUTPIXEL &   putPixel)
            {
                const unit_t dx  =  IntegerAbs(x1-x0), sx = (x0<x1) ? 1 : -1;
                const unit_t dy  = -IntegerAbs(y1-y0), sy = (y0<y1) ? 1 : -1;
                unit_t       err = dx+dy; /* error value e_xy */

                for(;;){  /* loop */
                    putPixel(x0,y0);
                    if (x0==x1 && y0==y1) break;
                    const unit_t e2 = 2*err;
                    if (e2 >= dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */
                    if (e2 <= dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */
                }
            }

            //!  one-argument line drawing
            /**
             \param x0 initial x
             \param y0 initial y
             \param x1 final x
             \param y1 final y
             \param putPixel putPixel(x,y,arg1) on each line point
             \param arg1     argument1
             */
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

            //!  two-arguments line drawing
            /**
             \param x0 initial x
             \param y0 initial y
             \param x1 final x
             \param y1 final y
             \param putPixel putPixel(x,y,arg1,arg2) on each line point
             \param arg1     argument1
             \param arg2     argument2
             */
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

            //!  three-arguments line drawing
            /**
             \param x0 initial x
             \param y0 initial y
             \param x1 final x
             \param y1 final y
             \param putPixel putPixel(x,y,arg1,arg2,arg3) on each line point
             \param arg1     argument1
             \param arg2     argument2
             \param arg3     argument3
             */
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

#include "y/ink/draw/clip.hpp"

namespace Yttrium
{

    namespace Ink
    {

        namespace Draw
        {
            //! no-extra argument clipped line
            /**
             \param img derived from area, passed to putPixel
             \param x0 initial x
             \param y0 initial y
             \param x1 final x
             \param y1 final y
             \param putPixel putPixel(x,y,img) on each line point
             */
            template <typename IMAGE, typename PUTPIXEL> inline
            void Line(const IMAGE &img,
                      unit_t       x0,
                      unit_t       y0,
                      unit_t       x1,
                      unit_t       y1,
                      PUTPIXEL &   putPixel)
            {
                if( Clip::Accept(x0,y0,x1,y1,img) )
                    Line_(x0,y0,x1,y1,putPixel,img);
            }

            //! 1-extra argument clipped line
            /**
             \param img derived from area, passed to putPixel
             \param x0 initial x
             \param y0 initial y
             \param x1 final x
             \param y1 final y
             \param putPixel putPixel(x,y,img,arg2) on each line point
             \param arg2 extra argument
             */
            template <typename IMAGE, typename PUTPIXEL, typename ARG2> inline
            void Line(const IMAGE &img,
                      unit_t       x0,
                      unit_t       y0,
                      unit_t       x1,
                      unit_t       y1,
                      PUTPIXEL &   putPixel,
                      ARG2     &   arg2)
            {
                if( Clip::Accept(x0,y0,x1,y1,img) )
                    Line_(x0,y0,x1,y1,putPixel,img,arg2);
            }
        }

    }

}



#endif // !Y_Ink_Draw_Line_Included
