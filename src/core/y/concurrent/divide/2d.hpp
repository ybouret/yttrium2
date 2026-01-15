//! \file


#ifndef Y_Concurrent_Divide2D_Included
#define Y_Concurrent_Divide2D_Included 1

#include "y/concurrent/divide/1d.hpp"
#include "y/concurrent/divide/box.hpp"
#include "y/concurrent/divide/hsegment.hpp"
#include "y/object/school-of.hpp"
#include "y/pointer/arc.hpp"

namespace Yttrium
{
    namespace Concurrent
    {
        namespace Divide
        {

           

            //! helper
#define Y_Tile2D_Ctor() h(0), n(0), segments( new SegsMem(1) )

            //__________________________________________________________________
            //
            //
            //
            //! Tile of horizontal segments
            //
            //
            //__________________________________________________________________
            template <typename T>
            class Tile2D : public Subdivision
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                typedef V2D<T>                    vertex_t; //!< alias
                typedef T                         scalar_t; //!< alias
                typedef Box<vertex_t>             BoxType;  //!< alias
                typedef HSegment<T>               SegType;  //!< alias
                typedef Memory::SchoolOf<SegType> SegsMem;  //!< alias
                typedef ArcPtr<SegsMem>           Segments; //!< alias

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup
                /**
                 \param sz  sz>0
                 \param rk  rk<sz
                 \param box total area
                 */
                inline explicit Tile2D(const size_t   sz,
                                       const size_t   rk,
                                       const BoxType &box) :
                Subdivision(sz,rk),
                Y_Tile2D_Ctor() {
                    setup(box);
                }

                //! setup
                /**
                 \param sz  sz>0
                 \param rk  rk<sz
                 */
                inline explicit Tile2D(const size_t   sz,
                                       const size_t   rk) :
                Subdivision(sz,rk),
                Y_Tile2D_Ctor() {
                    assert( isEmpty() );
                }


                //! setup
                /**
                 \param member member
                 \param box    total area
                 */
                inline explicit Tile2D(const Member  &member,
                                       const BoxType &box) :
                Subdivision(member),
                Y_Tile2D_Ctor() {
                    setup(box);
                }

                //! duplicate with shared segments \param t another tile
                inline Tile2D(const Tile2D &t) noexcept :
                Subdivision(t),
                h(t.h), n(t.n),
                segments(t.segments)
                {

                }

                //! cleanup
                inline virtual ~Tile2D() noexcept {
                }

                //! display
                inline friend std::ostream & operator<<(std::ostream &os, const Tile2D &t)
                {
                    if(t.h<=0)
                        os << Empty;
                    else
                        os << "|" << t.origin() << "->" << t.finish() << "|=" << t.n << "/#" << t.h;
                    return os;
                }

                //______________________________________________________________
                //
                //
                // Interface
                //
                //______________________________________________________________
                inline virtual bool isEmpty() const noexcept { return h<=0; }

                //______________________________________________________________
                //
                //
                // Method
                //
                //______________________________________________________________

                //! \return finish coordinate
                inline vertex_t finish() const noexcept
                {
                    return (h>0) ? segments->cxx[h].right() : vertex_t();
                }

                //! \return origin coordinate
                inline vertex_t origin() const noexcept
                {
                    return h>0 ? segments->entry[0].start : vertex_t();
                }


                //! \param j 1<=j<=h \return computed segment
                inline const SegType & operator[](const scalar_t j) const noexcept
                {
                    assert(j>0); assert(j<=h);
                    return segments->cxx[j];
                }


                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                const scalar_t h; //!< height
                const uint64_t n; //!< items

            private:
                Y_Disable_Assign(Tile2D); //!< discarding
                Segments segments;        //!< memory for segment

                //! setup algorithm
                /**
                 \param box  total working box
                 */
                inline void setup(const BoxType &box)
                {
                    static const scalar_t  one = 1;
                    static const scalar_t  id0 = 0;

                    //----------------------------------------------------------
                    // find indices
                    //----------------------------------------------------------
                    const Tile1D<scalar_t> tile1d(size,rank,box.count,id0);
                    if(tile1d.isEmpty()) return; // no data

                    //----------------------------------------------------------
                    // convert to vertices
                    //----------------------------------------------------------
                    const vertex_t ini = box.at(tile1d.offset);
                    const vertex_t end = box.at(tile1d.utmost);

                    //----------------------------------------------------------
                    // compute and allocate number of segments
                    //----------------------------------------------------------
                    {
                        const scalar_t required = end.y-ini.y+one;
                        const size_t   nhs      = (size_t)required;
                        if(nhs>segments->maxBlocks)
                        {
                            Segments tmp( new SegsMem(nhs) );
                            segments.xch(tmp);
                        }
                        Coerce(h) = required;
                    }

                    //----------------------------------------------------------
                    // convert to horizontal segments
                    //----------------------------------------------------------
                    const scalar_t htop = h-one;
                    for(scalar_t y=0;y<h;++y)
                    {
                        // lhs/rhs vertices from box
                        vertex_t lhs(box.lower.x,ini.y+y);
                        vertex_t rhs(box.upper.x,lhs.y);

                        // cut if necessary
                        if(y<=0)    lhs.x = ini.x;
                        if(y>=htop) rhs.x = end.x;
                        assert(lhs.y==rhs.y);
                        assert(rhs.x>=lhs.x);
                        const scalar_t w = one+rhs.x-lhs.x;

                        // record
                        new (segments->entry+y) SegType(lhs,w);
                        Coerce(n) += (uint64_t)w;
                    }
                }
            };


            //__________________________________________________________________
            //
            //
            //
            //! Tile2D partition
            //
            //
            //__________________________________________________________________
            template <typename T>
            class Tiles2D :
            public Writable< Tile2D<T> >,
            public Leap< V2D<T> >
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                typedef Tile2D<T>              Tile;      //!< alias
                typedef typename Tile::BoxType BoxType;   //!< alias
                typedef const BoxType &        Parameter; //!< alias
                typedef Writable<Tile2D<T>>    BaseType;  //!< alias


                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup
                /**
                 \param n   partition size
                 \param box total area
                 */
                inline explicit Tiles2D(const size_t   n,
                                        const BoxType  box) :
                BaseType(),
                Leap<V2D<T>>(box),
                tiles(n)
                {
                    for(size_t i=0;i<n;++i) tiles.push(n,i,box);
                }

                //! setup empty, with abnormal leap
                /**
                 \param n   partition size
                 */
                inline explicit Tiles2D(const size_t n) :
                BaseType(),
                Leap<V2D<T>>( V2D<T>(1,1), V2D<T>(0,0) ),
                tiles(n)
                {
                    for(size_t i=0;i<n;++i) tiles.push(n,i);
                }

                //! cleanup
                inline virtual ~Tiles2D() noexcept {}

                //______________________________________________________________
                //
                //
                // Interface
                //
                //______________________________________________________________
                inline virtual size_t size() const noexcept { return tiles.size(); }

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________

                //! \return readable interface
                inline const Readable< Tile2D<T> > & content() const noexcept
                {
                    return *this;
                }

                //! remap if necessary \param box new bounding box \return true if changed
                inline bool remap(const BoxType &box)
                {
                    // check same bounding box
                    {
                        const Leap< V2D<T> > &rhs = *this;
                        if( box == rhs ) return false;;
                    }

                    // create/exchange
                    {
                        Tiles2D t(tiles.size(),box);
                        tiles.xch(t.tiles);
                        Coerce(this->lower) = box.lower;
                        Coerce(this->upper) = box.upper;
                    }

                    return true;
                }


            private:
                Y_Disable_Copy_And_Assign(Tiles2D); //!< discarding
                CxxSeries<Tile> tiles; //!< computed tiles

                inline virtual const Tile & getItemAt(const size_t indx) const noexcept
                {
                    return tiles[indx];
                }
            };
        }

    }

}

#endif // !Y_Concurrent_Divide2D_Included

