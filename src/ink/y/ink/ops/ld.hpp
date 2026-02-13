
//! \file

#ifndef Y_Ink_Ld_Included
#define Y_Ink_Ld_Included 1

#include "y/ink/ops.hpp"

namespace Yttrium
{
    namespace Ink
    {

        struct LoadPixel
        {
            template <typename PIXMAP> static inline
            void Set(Broker &broker, PIXMAP &pixmap, typename PIXMAP::ParamType value)
            {
                Ops::Apply(broker, Put<PIXMAP,typename PIXMAP::MutableType>, pixmap,value);
            }

            template <typename PIXMAP, typename T>
            static void  Put(Lockable  &,
                             Ink::Tile &tile,
                             PIXMAP    &pxm,
                             const T   &arg)
            {
                for(unit_t k=tile.h;k>0;--k)
                {
                    const Ink::Segment    s   = tile[k];
                    typename PIXMAP::Row &row = pxm[s.start.y];
                    for(unit_t i=s.width,x=s.start.x;i>0;--i,++x)
                    {
                        row[x] = arg;
                    }
                }
            }

        };

    }

}

#endif // !Y_Ink_Ld_Included

