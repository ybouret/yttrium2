
//! \file


#ifndef Y_Concurrent_Divide2D_Included
#define Y_Concurrent_Divide2D_Included 1

#include "y/concurrent/divide/1d.hpp"
#include "y/concurrent/divide/box.hpp"
#include "y/mkl/v2d.hpp"
#include "y/object/school-of.hpp"
#include "y/pointer/arc.hpp"
#include "y/memory/stealth.hpp"

namespace Yttrium
{
    namespace Concurrent
    {
        namespace Divide
        {


            template <typename T>
            class HSegment
            {
            public:
                typedef T      scalar_t;
                typedef V2D<T> vertex_t;

                inline HSegment(const vertex_t v, const scalar_t w) noexcept :
                start(v),
                width(w)
                {
                }


                inline HSegment(const HSegment &hs) noexcept :
                start(hs.start),
                width(hs.width)
                {
                }

                inline ~HSegment() noexcept {}

                inline friend std::ostream & operator<<(std::ostream &os, const HSegment &self)
                {
                    vertex_t end = self.start; end.x += self.width; --end.x;
                    return os << "#" << self.width << ": " << self.start << "->" << end;
                }

                const vertex_t start;
                const scalar_t width;

            private:
                Y_Disable_Assign(HSegment);
            };

#define Y_Tile2D_Ctor()   h(0), segments( new SegsMem(1) )

            template <typename T>
            class Tile2D
            {
            public:
                typedef V2D<T>                    vertex_t;
                typedef T                         scalar_t;
                typedef Box<vertex_t>             BoxType;
                typedef HSegment<T>               SegType;
                typedef Memory::SchoolOf<SegType> SegsMem;
                typedef ArcPtr<SegsMem>           Segments;

                inline explicit Tile2D(const size_t   size,
                                       const size_t   indx,
                                       const BoxType &box) :
                Y_Tile2D_Ctor() {
                    setup(size,indx,box);
                }

                inline explicit Tile2D(const Member &member,
                                       const BoxType &box) :
                Y_Tile2D_Ctor() {
                    setup(member.size,member.indx,box);
                }

                inline Tile2D(const Tile2D &t) noexcept :
                h(t.h), segments(t.segments)
                {

                }


                inline virtual ~Tile2D() noexcept {
                    Memory::Stealth::Zero(segments->entry,segments->allocated);
                }

                inline const SegType & operator[](const scalar_t j) const noexcept
                {
                    assert(j>0); assert(j<=h);
                    return segments->cxx[j];
                }

                const scalar_t h;


            private:
                Y_Disable_Assign(Tile2D);
                Segments segments;

                inline void setup(const size_t size,
                                  const size_t indx,
                                  const BoxType &box)
                {
                    static const scalar_t  one = 1;
                    static const scalar_t  id0 = 0;
                    // find indices
                    const Tile1D<scalar_t> tile1d(size,indx,box.count,id0);
                    if(tile1d.length<=0) return; // no data

                    // convert to vertices
                    const vertex_t ini = box.at(tile1d.offset);
                    const vertex_t end = box.at(tile1d.utmost);

                    // compute and allocate number of segments
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

                    // convert to horizontal segments
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

                        // record
                        new (segments->entry+y) SegType(lhs,one+rhs.x-lhs.x);
                    }
                }
            };


            template <typename T>
            class Tiles2D : public Readable< Tile2D<T> >
            {
            public:
                typedef Tile2D<T>              Tile;
                typedef typename Tile::BoxType BoxType;

                inline explicit Tiles2D(const size_t   n,
                                        const BoxType &box) :
                tiles(n)
                {
                    for(size_t i=1;i<=n;++i)
                        tiles.push(n,i,box);
                }

                inline virtual ~Tiles2D() noexcept {}

                inline virtual size_t size() const noexcept { return tiles.size(); }

            private:
                Y_Disable_Copy_And_Assign(Tiles2D);
                CxxSeries<Tile> tiles;

                inline virtual const Tile & getItemAt(const size_t indx) const noexcept
                {
                    return tiles[indx];
                }
            };
        }

    }

}

#endif // !Y_Concurrent_Divide2D_Included

