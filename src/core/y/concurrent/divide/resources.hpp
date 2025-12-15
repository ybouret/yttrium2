//! \file

#ifndef Y_Concurrent_Resources_Included
#define Y_Concurrent_Resources_Included 1

#include "y/calculus/alignment.hpp"


namespace Yttrium
{
    namespace Concurrent
    {
        class Resources
        {
        public:
            explicit Resources() noexcept;
            virtual ~Resources() noexcept;

        protected:
            template <typename TILES> inline
            void giveEachTileOf(TILES &tiles, const size_t bytesPerTile)
            {
                const size_t numTiles = tiles.size();
                const size_t aligned  = Alignment::SystemMemory::Ceil(bytesPerTile);
                const size_t capacity = numTiles * aligned;
                ensure(capacity);
                assert(blockSize>=capacity);
                char * addr = (char *)blockAddr;
                for(size_t i=1;i<=numTiles;++i,addr+=aligned)
                {
                    Coerce(tiles[i].entry) = addr;
                    Coerce(tiles[i].bytes) = aligned;
                }
            }


        public:
            const size_t blockSize;
            void * const blockAddr;

        private:
            Y_Disable_Copy_And_Assign(Resources);
            void release() noexcept;
            void ensure(const size_t capacity);
        };
    }
}

#endif // !Y_Concurrent_Resources_Included

