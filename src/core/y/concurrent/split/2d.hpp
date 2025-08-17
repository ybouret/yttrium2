

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
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
            public:
                typedef ArcPtr<Tile>        Pointer; //!< alias
                typedef CxxArray< Pointer > Array;   //!< alias

                //______________________________________________________________
                //
                //
                //  C++
                //
                //______________________________________________________________
            protected:
                //! setup \param height number of segments
                inline explicit Tile(const size_t height) noexcept : s(0), h(height), items(0) {}
            public:
                //! cleanup[
                inline virtual ~Tile() noexcept {}

                //! display
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
                const HSegment<T> * const s;     //!< first segment address
                const size_t              h;     //!< number of segments = height
                const size_t              items; //!< total items

            private:
                Y_Disable_Copy_And_Assign(Tile); //!< discarding
            };

            //__________________________________________________________________
            //
            //
            //
            //! Empty Tile
            //
            //
            //__________________________________________________________________
            template <typename T>
            class EmptyTile : public Tile<T>
            {
            public:
                //______________________________________________________________
                //
                //
                //  C++
                //
                //______________________________________________________________
                inline explicit EmptyTile() noexcept : Tile<T>(0) {} //!< setup
                inline virtual ~EmptyTile() noexcept              {} //!< cleanup

            private:
                Y_Disable_Copy_And_Assign(EmptyTile); //!< discarding
            };


            //__________________________________________________________________
            //
            //
            //
            //! Metrics for In2D
            //
            //
            //__________________________________________________________________
            template <typename T>
            class Metrics2D
            {
            public:
                typedef V2D<T>      Coord; //!< alias
                typedef V2D<size_t> Count; //!< alias

                //______________________________________________________________
                //
                //
                //  C++
                //
                //______________________________________________________________

                //! setup \param lo lower coord \param up upper coords
                explicit Metrics2D(Coord lo, Coord up) noexcept :
                lower(lo),
                upper(up),
                width(),
                items(0)
                {
                    setup();
                }

                //! cleanup
                inline virtual ~Metrics2D() noexcept {}

                //______________________________________________________________
                //
                //
                //  Methods
                //
                //______________________________________________________________

                //! \param indx index in [0..items-1] \return matching coordinate
                Coord coord(const size_t indx) const noexcept
                {
                    assert(indx<items);
                    const size_t dy = indx / width.x;
                    const size_t dx = indx - dy * width.x;
                    assert(dx+width.x*dy==indx);
                    return Coord( (T)(lower.x+dx),(T)(lower.y+dy));
                }

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                const Coord  lower; //!< lower coordinates
                const Coord  upper; //!< upper coordinates
                const Count  width; //!< widths
                const size_t items; //!< number of items

            private:
                Y_Disable_Copy_And_Assign(Metrics2D); //!< discarding

                //! recomputing all
                inline void setup() noexcept
                {
                    if(lower.x>upper.x) CoerceSwap(lower.x,upper.x);
                    if(lower.y>upper.y) CoerceSwap(lower.y,upper.y);
                    ++(Coerce(width.x) = upper.x - lower.x);
                    ++(Coerce(width.y) = upper.y - lower.y);
                    Coerce(items) = width.x * width.y;
                }
            };

            //__________________________________________________________________
            //
            //
            //
            //! Heavy Tile
            //
            //
            //__________________________________________________________________
            template <typename T>
            class HeavyTile : public Tile<T>
            {
            public:
                using Tile<T>::s;
                using Tile<T>::h;
                using Tile<T>::items;

                //! setup
                /**
                 \param lo lower coordinate
                 \param up upper coordinate
                 \param metrics source metrics
                 */
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

                inline virtual ~HeavyTile() noexcept {} //!< cleanup

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
            private:
                Y_Disable_Copy_And_Assign(HeavyTile); //!< discarding
                typename HSegment<T>::Array arr;      //!< segments
            };

            //__________________________________________________________________
            //
            //
            //
            //! base class for tiles
            //
            //
            //__________________________________________________________________
            template <typename T>
            class TilesComm
            {
            public:
                inline explicit TilesComm() : empty( new EmptyTile<T>() ) {} //!< setup
                inline virtual ~TilesComm() noexcept {}                      //!< cleanup

            private:
                Y_Disable_Copy_And_Assign(TilesComm); //!< discarding
            protected:
                const typename Tile<T>::Pointer empty; //!< empty tile
            };


            //__________________________________________________________________
            //
            //
            //
            //! precomputed tiles
            //
            //
            //__________________________________________________________________
            template <typename T>
            class Tiles :
            public TilesComm<T>,
            public Ingress< const Readable< typename Tile<T>::Pointer > >
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                typedef Tile<T>                        TileType;    //!< alias
                typedef typename TileType::Pointer     TilePointer; //!< alias
                typedef typename TileType::Array       TileArray;   //!< alias

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup \param numProcessors parallel size
                inline explicit Tiles(const size_t numProcessors) :
                TilesComm<T>(),
                arr(numProcessors,this->empty)
                {
                    assert(numProcessors>0);
                }

                //! cleanup
                inline virtual ~Tiles() noexcept
                {

                }

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________

                //! reset all to empty
                inline void reset() noexcept
                {
                    for(size_t i=arr.size();i>0;--i)
                    {
                        arr[i] = this->empty;
                    }
                }

            private:
                Y_Disable_Copy_And_Assign(Tiles); //!< discarding
                inline virtual const TileArray & locus() const noexcept { return arr; }

                TileArray arr; //!< tiles
            };





            //__________________________________________________________________
            //
            //
            //
            //! In2D
            //
            //
            //__________________________________________________________________
            template <typename T>
            class In2D : public Metrics2D<T>
            {
            public:
                typedef Metrics2D<T>                MetricsType; //!< alias
                typedef Tile<T>                     TileType;    //!< alias
                typedef typename MetricsType::Coord Coord;       //!< alias
                typedef typename MetricsType::Count Count;       //!< alias
                using MetricsType::items;

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup \param lo lower coordinate \param up upper coordinate
                explicit In2D(Coord lo, Coord up) noexcept :
                MetricsType(lo,up),
                in1d(items)
                {
                }

                //! prepare \param numProcessors number of tiles
                void boot(const size_t numProcessors) noexcept
                {
                    in1d.boot(numProcessors,0);
                }

                //! \return Empty/Heavy tile, NULL when done
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

                //! split metrics \param tiles tiling \return tiles
                inline Tiles<T> & operator()(Tiles<T> &tiles)
                {
                    const size_t np  = tiles->size();
                    tiles.reset();
                    boot(np);
                    for(size_t i=1;i<=np;++i)
                    {
                        Tile<T> * const tile = next(); assert(0!=tile);
                        const typename Tile<T>::Pointer p(tile);
                        Coerce( (*tiles)[i] ) = p;
                    }
                    return tiles;
                }




                //! cleanup
                virtual ~In2D() noexcept
                {

                }

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
            private:
                In1D in1d; //!< indexing in 1D
                Y_Disable_Copy_And_Assign(In2D); //!< discarding
            };



        }


    }

}

#endif

