
//! \file


#ifndef Y_Concurrent_Divide2D_Included
#define Y_Concurrent_Divide2D_Included 1

#include "y/concurrent/divide/1d.hpp"
#include "y/concurrent/divide/box.hpp"
#include "y/mkl/v2d.hpp"

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

