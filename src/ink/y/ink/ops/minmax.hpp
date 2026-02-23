

//! \file

#ifndef Y_Ink_MinMax_Included
#define Y_Ink_MinMax_Included 1

#include "y/ink/broker.hpp"
#include "y/ink/pixmap.hpp"

namespace Yttrium
{
    namespace Ink
    {
        template <typename T>
        class PixelValue
        {
        public:
            inline  PixelValue() : vmin(0), vmax(0) {}
            inline  PixelValue(const PixelValue &_) : vmin(_.vmin), vmax(_.vmax) {}
            inline ~PixelValue() noexcept {}
            inline  PixelValue(const T pmin, const T pmax) : vmin(pmin), vmax(pmax) {}
            inline PixelValue(const T * const addr) : vmin(addr[0]), vmax(addr[1]) {}
            inline PixelValue & operator=(const PixelValue &_)
            {
                vmin = _.vmin;
                vmax = _.vmax;
                return *this;
            }
            inline void updateWith(const PixelValue &other)
            {
                InSituMin(vmin,other.vmin);
                InSituMax(vmax,other.vmax);
            }
            T vmin;
            T vmax;
        };


        struct MinMax
        {
            template <typename T> static inline
            PixelValue<T> Of(Broker &broker, const Pixmap<T> &pixmap)
            {
                broker.prep(pixmap);
                broker.acquireLocalMemory( sizeof( PixelValue<T> ) );
                broker.run(MinMaxOfTile<T>,pixmap);
                size_t i = broker.size(); assert(i>0); assert( !broker[i].isEmpty() );
                PixelValue<T> res = broker[i].as< PixelValue<T> >();
                for(--i;i>0;--i)
                {
                    const Tile &tile = broker[i]; if(tile.isEmpty()) break;
                    res.updateWith( tile.as< PixelValue<T> > () );
                }
                return res;
            }

            template <typename T>
            static inline void MinMaxOfTile(Lockable &, Ink::Tile &tile, const Pixmap<T> &pxm)
            {
                assert(tile.entry);
                assert(tile.bytes>=sizeof(PixelValue<T>));
                if(tile.isEmpty()) return;
                T * const addr = static_cast<T *>(tile.entry);
                T & vmin = ( addr[0] = pxm[ tile.origin() ]);
                T & vmax = ( addr[1] = addr[0] );
                for(unit_t j=tile.h;j>0;--j)
                {
                    const Segment                   s = tile[j];
                    const typename Pixmap<T>::Row & r = pxm[s.start.y];
                    for(unit_t i=s.width,x=s.start.x;i>0;--i,++x)
                    {
                        const T & v = r[x];
                        InSituMin(vmin,v);
                        InSituMax(vmax,v);
                    }
                }
            }

        };

    }

}

#endif // !Y_Ink_MinMax_Included

