

//! \file

#ifndef Y_Ink_MinMax_Included
#define Y_Ink_MinMax_Included 1

#include "y/ink/broker.hpp"
#include "y/ink/pixmap.hpp"

namespace Yttrium
{
    namespace Ink
    {
#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
        template <typename T>
        class PixelRange
        {
        public:
            inline  PixelRange() : vmin(0), vmax(0) {}
            inline  PixelRange(const PixelRange &_) : vmin(_.vmin), vmax(_.vmax) {}
            inline ~PixelRange() noexcept {}
            inline  PixelRange(const T pmin, const T pmax) : vmin(pmin), vmax(pmax) {}
            inline  PixelRange(const T * const addr) : vmin(addr[0]), vmax(addr[1]) {}
            inline  PixelRange & operator=(const PixelRange &_)
            {
                vmin = _.vmin;
                vmax = _.vmax;
                return *this;
            }
            inline void updateWith(const PixelRange &other)
            {
                InSituMin(vmin,other.vmin);
                InSituMax(vmax,other.vmax);
            }
            T vmin;
            T vmax;
        };
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)

        //______________________________________________________________________
        //
        //
        //
        //! Get maximum/minimum of pixmap
        //
        //
        //______________________________________________________________________
        struct MinMax
        {
            //! \param broker cpu broker \param pixmap source \return range value
            template <typename T> static inline
            PixelRange<T> Of(Broker &broker, const Pixmap<T> &pixmap)
            {
                broker.prep(pixmap);
                broker.acquireLocalMemory( sizeof( PixelRange<T> ) );
                broker.run(MinMaxOfTile<T>,pixmap);
                size_t i = broker.size(); assert(i>0); assert( !broker[i].isEmpty() );
                PixelRange<T> res = broker[i].as< PixelRange<T> >();
                for(--i;i>0;--i)
                {
                    const Tile &tile = broker[i]; if(tile.isEmpty()) break;
                    res.updateWith( tile.as< PixelRange<T> > () );
                }
                return res;
            }

        private:
            //! \param tile tile to probe \param pxm source
            template <typename T>
            static inline void MinMaxOfTile(Lockable &, Ink::Tile &tile, const Pixmap<T> &pxm)
            {
                assert(tile.entry);
                assert(tile.bytes>=sizeof(PixelRange<T>));
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

