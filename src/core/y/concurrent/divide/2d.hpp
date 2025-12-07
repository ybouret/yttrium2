
//! \file


#ifndef Y_Concurrent_Divide2D_Included
#define Y_Concurrent_Divide2D_Included 1

#include "y/concurrent/divide/1d.hpp"
#include "y/concurrent/divide/box.hpp"
#include "y/mkl/v2d.hpp"
#include "y/object/school-of.hpp"

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

                const vertex_t start;
                const scalar_t width;

            private:
                Y_Disable_Assign(HSegment);
            };

            template <typename T>
            class Tile2D : public Object
            {
            public:
                typedef V2D<T>                    vertex_t;
                typedef T                         scalar_t;
                typedef Box<vertex_t>             BoxType;
                typedef HSegment<T>               SegType;
                typedef Memory::SchoolOf<SegType> Segments;

                inline explicit Tile2D(const size_t   size,
                                       const size_t   indx,
                                       const BoxType &box) :
                Object(), height(0), segments(0) {
                    setup(size,indx,box);
                }

                inline explicit Tile2D(const Member &member,
                                       const BoxType &box) :
                Object(), height(0), segments(0) {
                    setup(member.size,member.indx,box);
                }


                inline virtual ~Tile2D() noexcept
                {
                }

                inline const SegType & operator[](const scalar_t j) const noexcept
                {
                    assert(j>0);
                    assert(j<=height);
                    return segments.cxx[j];
                }

                const scalar_t height;


            private:
                Y_Disable_Assign(Tile2D);
                Segments segments;

                inline void setup(const size_t size,
                                  const size_t indx,
                                  const BoxType &box)
                {
                    static const scalar_t  one = 1;
                    // find items
                    const Tile1D<scalar_t> tile1d(size,indx,box.count,0);
                    if(tile1d.length<=0) return; // no data

                    // convert to vertices
                    const vertex_t ini = box.at(tile1d.offset);
                    const vertex_t end = box.at(tile1d.utmost);
                    {
                        const scalar_t nhs = end.y-ini.y+one;
                        std::cerr << ini << " -> " << end << " #hseg=" << nhs << std::endl;
                        {
                            Segments tmp(nhs);
                            segments.exchange(tmp);
                        }
                        Coerce(height) = nhs;
                    }

                    for(scalar_t h=0;h<height;++h)
                    {
                        vertex_t org(box.lower.x,ini.y+h);
                        vertex_t end(box.upper.x,org.y);
                        //new (segments.entry+h) SegType(
                    }
                }
            };

        }

    }

}

#endif // !Y_Concurrent_Divide2D_Included

