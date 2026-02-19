
//! \file

#ifndef Y_Ink_GetMax_Included
#define Y_Ink_GetMax_Included 1

#include "y/ink/broker.hpp"
#include "y/ink/pixmap.hpp"

namespace Yttrium
{
    namespace Ink
    {
        struct GetMax
        {
            template <typename T> static inline
            T Of(Broker &broker, const Pixmap<T> &pixmap)
            {
                const T zero = 0;
                broker.prep(pixmap);
                broker.acquireLocalMemory( sizeof(T) );
                broker.run(MaxOfTile<T>,pixmap,zero);
                size_t i = broker.size(); assert(i>0); assert( !broker[i].isEmpty() );
                T res = broker[i].as<T>();
                for(--i;i>0;--i)
                {
                    const Tile &tile = broker[i]; if(tile.isEmpty()) break;
                    InSituMax(res,tile.as<T>());
                }
                return res;
            }

            template <typename T>
            static inline void MaxOfTile(Lockable &, Ink::Tile &tile, const Pixmap<T> &pxm, const T &zero)
            {
                assert(tile.entry);
                assert(tile.bytes>=sizeof(T));
                T & res = (tile.as<T>() = zero);
                for(unit_t j=tile.h;j>0;--j)
                {
                    const Segment                   s = tile[j];
                    const typename Pixmap<T>::Row & r = pxm[s.start.y];
                    for(unit_t i=s.width,x=s.start.x;i>0;--i,++x)
                        InSituMax(res,r[x]);
                }
            }

        };

    }

}

#endif // !Y_Ink_GetMax_Included

