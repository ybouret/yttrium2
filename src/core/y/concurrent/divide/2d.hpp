
//! \file


#ifndef Y_Concurrent_Divide2D_Included
#define Y_Concurrent_Divide2D_Included 1

#include "y/concurrent/divide/1d.hpp"
#include "y/concurrent/divide/box.hpp"
#include "y/mkl/v2d.hpp"
#include "y/object/school-of.hpp"
#include "y/pointer/arc.hpp"

namespace Yttrium
{
    namespace Concurrent
    {
        namespace Divide
        {

            //__________________________________________________________________
            //
            //
            //
            //! Generic Horizontal Segment
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
                typedef T      scalar_t; //!< alias
                typedef V2D<T> vertex_t; //!< alias

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup \param v start \param w width > 0
                inline HSegment(const vertex_t v, const scalar_t w) noexcept :
                start(v),
                width(w)
                {
                    assert(w>0);
                }


                //! duplicate \param hs another segment
                inline HSegment(const HSegment &hs) noexcept :
                start(hs.start),
                width(hs.width)
                {
                }

                //! cleanup
                inline ~HSegment() noexcept {}

                //! display
                inline friend std::ostream & operator<<(std::ostream &os, const HSegment &self)
                {
                    vertex_t end = self.start; end.x += self.width; --end.x;
                    return os << "#" << self.width << ": " << self.start << "->" << end;
                }

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________

                //! \return rightmost coordinate
                inline vertex_t right() const noexcept { vertex_t _(start.x+width,start.y); --_.x; return _; }

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                const vertex_t  start; //!< starting point
                const scalar_t  width; //!< width

            private:
                Y_Disable_Assign(HSegment); //!< discarding
            };

            //! helper
#define Y_Tile2D_Ctor()   Subdivision(), h(0), n(0), segments( new SegsMem(1) )

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
                 \param size size>0
                 \param indx 1<=indx<=size
                 \param box  total area
                 */
                inline explicit Tile2D(const size_t   size,
                                       const size_t   indx,
                                       const BoxType &box) :
                Y_Tile2D_Ctor() {
                    setup(size,indx,box);
                }

                //! setup
                /**
                 \param member member
                 \param box    total area
                 */
                inline explicit Tile2D(const Member &member,
                                       const BoxType &box) :
                Y_Tile2D_Ctor() {
                    setup(member.size,member.indx,box);
                }

                //! duplicate with shared segments \param t another tile
                inline Tile2D(const Tile2D &t) noexcept :
                h(t.h), n(t.n), segments(t.segments)
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
                virtual bool isEmpty() const noexcept { return h<=0; }

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
                 \param size member size
                 \param indx member index
                 \param box  total working box
                 */
                inline void setup(const size_t size,
                                  const size_t indx,
                                  const BoxType &box)
                {
                    static const scalar_t  one = 1;
                    static const scalar_t  id0 = 0;

                    //----------------------------------------------------------
                    // find indices
                    //----------------------------------------------------------
                    const Tile1D<scalar_t> tile1d(size,indx,box.count,id0);
                    if(tile1d.length<=0) return; // no data

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
            class Tiles2D : public Readable< Tile2D<T> >
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
                                        const BoxType &box) : tiles(n) {
                    for(size_t i=1;i<=n;++i) tiles.push(n,i,box);
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

