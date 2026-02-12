
#include "y/ink/draw/clip.hpp"

namespace Yttrium
{

    namespace Ink
    {
        Clip::Status Clip:: StatusOf(const unit_t x, const unit_t y, const Area &area) noexcept
        {

            Status res = Inside;

            if( x < area.lower.x ) res |= Left;
            if( x > area.upper.x ) res |= Right;
            if( y < area.lower.y ) res |= Bottom;
            if( y > area.upper.y ) res |= Top;

            return res;
        }

        bool Clip:: Accept(unit_t &x0, unit_t &y0,
                           unit_t &x1, unit_t &y1,
                           const Area & area) noexcept
        {
            const unit_t xmin  = area.lower.x;
            const unit_t xmax  = area.upper.x;
            const unit_t ymin  = area.lower.y;
            const unit_t ymax  = area.upper.y;
            Status       code0 = StatusOf(x0,y0,area);
            Status       code1 = StatusOf(x1,y1,area);
            while(true)
            {
                if( ! (code0|code1)    ) return true;  // both inside
                if( 0 != (code0&code1) ) return false; // sharing some outside part => invisible

                // At least one endpoint is outside: pick it.
                const Status codeOut =  code1 > code0 ?  code1 :  code0;
                unit_t       x=0,y=0;

                if (codeOut & Top) { // point is above the clip window
                    x = x0 + (x1 - x0) * (ymax - y0) / (y1 - y0);
                    y = ymax;
                    goto UPDATE;
                }

                if(codeOut & Bottom) { // point is below the clip windo
                    x = x0 + (x1 - x0) * (ymin - y0) / (y1 - y0);
                    y = ymin;
                    goto UPDATE;
                }

                if (codeOut & Right) {  // point is to the right of clip window
                    y = y0 + (y1 - y0) * (xmax - x0) / (x1 - x0);
                    x = xmax;
                    goto UPDATE;
                }

                if (codeOut & Left) {   // point is to the left of clip window
                    y = y0 + (y1 - y0) * (xmin - x0) / (x1 - x0);
                    x = xmin;
                    goto UPDATE;
                }

            UPDATE:
                // Now we move outside point to intersection point to clip
                // and get ready for next pass.
                if (code0 == codeOut) {
                    x0 = x;
                    y0 = y;
                    code0 = StatusOf(x0,y0,area);
                } else {
                    x1 = x;
                    y1 = y;
                    code1 = StatusOf(x1,y1,area);
                }
            }

        }

    }

}
