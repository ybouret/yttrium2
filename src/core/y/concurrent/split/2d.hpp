

//! \file


#ifndef Y_Concurrent_Split2D_Included
#define Y_Concurrent_Split2D_Included 1

#include "y/concurrent/split/1d.hpp"
#include "y/mkl/v2d.hpp"
#include "y/object/counted.hpp"
#include "y/container/cxx/series.hpp"

namespace Yttrium
{
    namespace Concurrent
    {

        namespace Split
        {

            //__________________________________________________________________
            //
            //
            //
            //! Horizontal Segment
            //
            //
            //__________________________________________________________________
            template <typename T>
            class HSegment
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                typedef CxxSeries<HSegment> Array; //!< alias

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup
                /**
                 \param x0 original x
                 \param y0 original y
                 \param x1 final x
                 */
                inline HSegment(const T x0, const T y0, const T x1) noexcept :
                y(y0),
                x(x0),
                w(x1-x0+1),
                x_end(x1)
                {
                }

                //! cleanup
                inline ~HSegment() noexcept {}

                //! duplicate \param s another segment
                inline  HSegment(const HSegment &s) noexcept : y(s.y), x(s.x), w(s.w),x_end(s.x_end) {}

                //! display
                inline friend std::ostream & operator<<(std::ostream &os, const HSegment &self)
                {
                    os
                    << '[' << self.x << ':' << self.y << ']'
                    << "->"
                    << '[' << self.x_end << ':' << self.y << ']'
                    << '#' << self.w;
                    return os;
                }

                //______________________________________________________________
                //
                //
                //  Members
                //
                //______________________________________________________________
                const T      y;     //!< original y
                const T      x;     //!< original x
                const size_t w;     //!< width
                const T      x_end; //!< final x

            private:
                Y_Disable_Assign(HSegment); //!< discarding
            };


            //__________________________________________________________________
            //
            //
            //
            //! Tile of Horizontal segments
            //
            //
            //__________________________________________________________________
            template <typename T>
            class Tile : public CountedObject
            {
            protected:
                inline explicit Tile(const size_t height) noexcept : s(0), h(height), items(0) {}
            public:
                inline virtual ~Tile() noexcept {}

                inline friend std::ostream & operator<<(std::ostream &os, const Tile &tile)
                {
                    if(tile.h<=0)
                    {
                        os << "[empty tile]";
                    }
                    else
                    {
                        os << "h=" << tile.h << ", items=" << tile.items;
                        for(size_t j=0;j<tile.h;++j)
                        {
                            os << std::endl << '\t' << tile.s[j];
                        }
                    }
                    return os;
                }

                //______________________________________________________________
                //
                //
                //  Members
                //
                //______________________________________________________________
                const HSegment<T> * const s; //!< first segment address
                const size_t              h; //!< number of segments = height
                const size_t              items; //

            private:
                Y_Disable_Copy_And_Assign(Tile);
            };


            template <typename T>
            class EmptyTile : public Tile<T>
            {
            public:
                inline explicit EmptyTile() noexcept : Tile<T>(0) {}
                inline virtual ~EmptyTile() noexcept              {}

            private:
                Y_Disable_Copy_And_Assign(EmptyTile);
            };

            
            template <typename T>
            class Metrics2D
            {
            public:
                typedef V2D<T>      Coord;
                typedef V2D<size_t> Count;
                explicit Metrics2D(Coord lo, Coord up) noexcept :
                lower(lo),
                upper(up),
                width(),
                items(0)
                {
                    setup();
                }

                inline virtual ~Metrics2D() noexcept {}

                Coord coord(const size_t indx) const noexcept
                {
                    assert(indx<items);
                    const size_t dy = indx / width.x;
                    const size_t dx = indx - dy * width.x;
                    assert(dx+width.x*dy==indx);
                    return Coord( (T)(lower.x+dx),(T)(lower.y+dy));
                }

                const Coord  lower;
                const Coord  upper;
                const Count  width;
                const size_t items;

            private:
                Y_Disable_Copy_And_Assign(Metrics2D);
                inline void setup() noexcept
                {
                    if(lower.x>upper.x) CoerceSwap(lower.x,upper.x);
                    if(lower.y>upper.y) CoerceSwap(lower.y,upper.y);
                    ++(Coerce(width.x) = upper.x - lower.x);
                    ++(Coerce(width.y) = upper.y - lower.y);
                    Coerce(items) = width.x * width.y;
                }
            };


            template <typename T>
            class HeavyTile : public Tile<T>
            {
            public:
                using Tile<T>::s;
                using Tile<T>::h;
                using Tile<T>::items;

                inline explicit HeavyTile(const V2D<T>       &lo,
                                          const V2D<T>       &up,
                                          const Metrics2D<T> &metrics) :
                Tile<T>(up.y-lo.y+1),
                arr(h)
                {
                    assert(h>0);
                    T y = lo.y;
                    for(size_t j=1;j<=h;++j,++y)
                    {
                        const T x_lo = (j==1) ? lo.x : metrics.lower.x;
                        const T x_up = (j==h) ? up.x : metrics.upper.x;
                        const HSegment<T> s(x_lo,y,x_up);
                        Coerce(arr)   << s;
                        Coerce(items) += s.w;
                    }
                    Coerce(s) = & arr[1];
                }

                inline virtual ~HeavyTile() noexcept
                {}


            private:
                Y_Disable_Copy_And_Assign(HeavyTile);
                typename HSegment<T>::Array arr;


            };


            template <typename T>
            class In2D : public Metrics2D<T>
            {
            public:
                typedef Metrics2D<T>                MetricsType;
                typedef Tile<T>                     TileType;
                typedef typename MetricsType::Coord Coord;
                typedef typename MetricsType::Count Count;
                using MetricsType::items;

                explicit In2D(Coord lo, Coord up) noexcept :
                MetricsType(lo,up),
                in1d(items)
                {
                }

                void boot(const size_t numProcessors) noexcept
                {
                    in1d.boot(numProcessors,0);
                }

                Tile<T> * next()
                {
                    if(!in1d.next()) return 0;

                    const size_t offset = in1d.offset;
                    const size_t length = in1d.length;
                    if(length>0)
                    {
                        const size_t oflast = offset+length-1;
                        const Coord  lo     = this->coord(offset);
                        const Coord  up     = this->coord(oflast);
                        //std::cerr << "from " << offset << " to " << oflast << " #" << length << " " << lo << " -> " << up << std::endl;
                        assert(lo.y<=up.y);
                        return new HeavyTile<T>(lo,up,*this);
                    }
                    else
                    {
                        //std::cerr << "empty" << std::endl;
                        return new EmptyTile<T>();
                    }
                }


                virtual ~In2D() noexcept
                {

                }


            private:
                In1D in1d;
                Y_Disable_Copy_And_Assign(In2D);
            };



        }


    }

}

#endif

