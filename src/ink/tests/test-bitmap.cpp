
#include "y/ink/bitmap.hpp"
#include "y/utest/run.hpp"
#include "y/container/contiguous.hpp"
#include "y/random/park-miller.hpp"
#include <cstring>

#include "y/concurrent/divide/2d.hpp"
#include "y/concurrent/api/simd/spawn.hpp"

namespace Yttrium
{
    namespace Ink
    {

        typedef Concurrent::Divide::Tiles2D<unit_t> Tiles;
        typedef Tiles::BoxType                      Box;
        typedef Concurrent::Spawn<Tiles>            Tiling;

        class Dispatch : public Box, public Tiling
        {
        public:
            explicit Dispatch(const Concurrent::Processor &sharedProc,
                              const Area                  &area) :
            Box(area.lower,area.upper),
            Tiling(sharedProc,bbox())
            {
            }

            virtual ~Dispatch() noexcept
            {
            }

        private:
            Y_Disable_Copy_And_Assign(Dispatch);
            const Box & bbox() const noexcept { return *this; }
        };


    }
}

using namespace Yttrium;



namespace
{
    template <typename T> class SomeRow
    {
    public:

        T & operator[](const unit_t i) noexcept
        {
            assert(p);
            return p[ z[i] ];
        }


    private:
        T * const            p;
    public:
        const size_t         w;
        const Ink::ZeroFlux &z;

    private:
        SomeRow() noexcept;
        ~SomeRow() noexcept;
        Y_Disable_Copy_And_Assign(SomeRow);
    };

    static inline void ctor(void * const addr, const void * const)  { new (addr) uint32_t(0); }
    static inline void dtor(void * const addr) noexcept { memset(addr,0,sizeof(uint32_t));  }
    


}

Y_UTEST(bitmap)
{
    Random::ParkMiller ran;
    Ink::Bitmap        bmp(100,34,sizeof(uint32_t),ctor,dtor);



    for(unit_t j=0;j<bmp.upper.y;++j)
    {
        Ink::BitRow &       r   = bmp.getRow( (size_t)j );
        SomeRow<uint32_t> & row = (SomeRow<uint32_t>&)(r);
        for(unit_t i=bmp.lower.y;i<=bmp.upper.y;++i)
        {
            row[i] = ran.to<uint32_t>();
        }

    }
    
}
Y_UDONE()
