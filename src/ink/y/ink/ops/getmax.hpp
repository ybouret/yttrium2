
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
                return zero;
            }

            template <typename T>
            static inline void MaxOfTile(Lockable &, Ink::Tile &tile, const Pixmap<T> &pxm, const T &zero)
            {
                assert(tile.entry);
                assert(tile.bytes>=sizeof(T));
                T & res = (tile.as<T>() = zero);

            }

        };

    }

}

#endif // !Y_Ink_GetMax_Included

