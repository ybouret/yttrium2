
//! \file


#ifndef Y_Concurrent_Divide2D_Included
#define Y_Concurrent_Divide2D_Included 1

#include "y/concurrent/divide/1d.hpp"
#include "y/mkl/v2d.hpp"

namespace Yttrium
{
    namespace Concurrent
    {
        namespace Divide
        {

            template <typename VERTEX>
            class Box
            {
            public:
                typedef               VERTEX         vertex_t;
                typedef typename      VERTEX::Type   scalar_t;
                static const unsigned DIMENSIONS   = VERTEX::DIMENSIONS ;

                inline Box(const vertex_t lo,
                           const vertex_t up) :
                lower(lo),
                upper(up),
                width(),
                count()
                {

                }

                inline ~Box() noexcept
                {

                }

                const vertex_t lower;
                const vertex_t upper;
                const vertex_t width;
                const scalar_t count;



            private:
                Y_Disable_Copy_And_Assign(Box);

                static scalar_t Setup(vertex_t &lo,
                                      vertex_t &up,
                                      vertex_t &sz) noexcept
                {
                    static const scalar_t one(1);
                    scalar_t prod = 1;
                    for(unsigned i=1;i<=DIMENSIONS;++i)
                    {
                        if(lo[i]>up[i]) Swap(lo[i],up[i]);
                        prod *= ( sz[i] = one + up[i] - lo[i]);
                    }
                    return prod;
                }
            };

            

            template <typename T>
            class Tile2D
            {
            public:


            private:
                Y_Disable_Assign(Tile2D);
            };

        }

    }

}

#endif // !Y_Concurrent_Divide2D_Included

