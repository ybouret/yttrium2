

//! \file

#ifndef Y_Ink_Draw_Clip_Included
#define Y_Ink_Draw_Clip_Included

#include "y/ink/area.hpp"

namespace Yttrium
{

    namespace Ink
    {
        struct Clip
        {
            typedef unsigned Status;
            static const Status Inside = 0x00;
            static const Status Left   = 0x01;
            static const Status Right  = 0x02;
            static const Status Top    = 0x04;
            static const Status Bottom = 0x08;

            static Status StatusOf(const unit_t x, const unit_t y, const Area &area) noexcept;
            static bool   Accept(unit_t &x0, unit_t &y0,
                                 unit_t &x1, unit_t &y1,
                                 const Area & area) noexcept;


        };
    }

}

#endif // !Y_Ink_Draw_Clip_Included
