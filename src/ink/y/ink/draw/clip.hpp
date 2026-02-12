

//! \file

#ifndef Y_Ink_Draw_Clip_Included
#define Y_Ink_Draw_Clip_Included

#include "y/ink/area.hpp"

namespace Yttrium
{

    namespace Ink
    {
        //! Clipping Algorithm
        struct Clip
        {
            typedef unsigned Status;           //!< alias
            static const Status Inside = 0x00; //!< alias
            static const Status Left   = 0x01; //!< alias
            static const Status Right  = 0x02; //!< alias
            static const Status Top    = 0x04; //!< alias
            static const Status Bottom = 0x08; //!< alias

            //! get status of a point w.r.t. given area
            /**
             \param x x
             \param y y
             \param area given area
             \return relative wstatus
             */
            static Status StatusOf(const unit_t x,
                                   const unit_t y,
                                   const Area &area) noexcept;

            //! detect if line crosses the area
            /**
             \param x0 initial x
             \param y0 initial y
             \param x1 final   x
             \param y1 final   y
             \param area given area
             \return true iff something crosses the area
             */
            static bool   Accept(unit_t &x0, unit_t &y0,
                                 unit_t &x1, unit_t &y1,
                                 const Area & area) noexcept;


        };
    }

}

#endif // !Y_Ink_Draw_Clip_Included
