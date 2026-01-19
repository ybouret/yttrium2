
//! \file

#ifndef Y_Ink_Histogram_Included
#define Y_Ink_Histogram_Included 1

#include "y/ink/ops.hpp"
#include "y/memory/stealth.hpp"
namespace Yttrium
{
    namespace Ink
    {
        class Histogram
        {
        public:
            typedef uint32_t    Type;
            static const size_t Bins = 256;
            static const size_t LocalMemory = Bins * sizeof(Type);

            explicit Histogram() noexcept;
            virtual ~Histogram() noexcept;

            Histogram & ldz() noexcept;
            Type &       operator[](const uint8_t) noexcept;
            const Type & operator[](const uint8_t) const noexcept;

            Histogram & operator+= (const Type * const) noexcept;
            Histogram & operator+= (const Histogram &)  noexcept;

            friend bool operator==(const Histogram &, const Histogram &) noexcept;

            template <typename PIXMAP, typename PIXEL_TO_BYTE> inline
            void add(Broker &broker, const PIXMAP &pxm, PIXEL_TO_BYTE &proc)
            {
                broker.acquireLocalMemory( LocalMemory );
                broker.run(CallAdd<PIXMAP,PIXEL_TO_BYTE>,pxm,proc);
            }

        private:
            Y_Disable_Copy_And_Assign(Histogram);
            Type bin[Bins];

            template <typename PIXMAP, typename PIXEL_TO_BYTE> static
            inline void CallAdd(Lockable      &,
                                const Tile    & tile,
                                const PIXMAP  & pxm,
                                PIXEL_TO_BYTE & proc)
            {
                assert( tile.entry );
                assert( tile.bytes >= LocalMemory );
                assert( Memory::Stealth::Are0(tile.entry,tile.bytes) );
                Type * const h = static_cast<Type *>(tile.entry);
                for(size_t k=tile.h;k>0;--k)
                {
                    const Segment              &s = tile[k];
                    const typename PIXMAP::Row &r = pxm[s.start.y];
                    for(unit_t n=s.width,x=s.start.x;n>0;--n,++x)
                        ++h[(uint8_t)proc(r[x])];
                }
            }
        };
    }

}

#endif // !Y_Ink_Histogram_Included
