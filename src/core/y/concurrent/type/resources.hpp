//! \file

#ifndef Y_Concurrent_Resources_Included
#define Y_Concurrent_Resources_Included 1

#include "y/calculus/alignment.hpp"


namespace Yttrium
{
    namespace Concurrent
    {

        //______________________________________________________________________
        //
        //
        //
        //! handle resources for tiles
        //
        //
        //______________________________________________________________________
        class Resources
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Resources() noexcept; //!< setup
            virtual ~Resources() noexcept; //!< cleanup

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            

        protected:

            //! ensure each tile has enough ZEROED bytes
            /**
             \param tiles        array of tile
             \param bytesPerTile bytes
             */
            template <typename TILES> inline
            void acquireEachTileOf(TILES &tiles, const size_t bytesPerTile)
            {
                const size_t numTiles = tiles.size(); assert(numTiles>0);
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

            //! release all memory \param tiles updated tiles
            template <typename TILES> inline
            void releaseEachTileOf(TILES &tiles) noexcept
            {
                clearEachTileOf(tiles);
                release();
            }

            //! assign each tile current memory part \param tiles each tile receive blockSize/numTiles
            template <typename TILES> inline
            void deliverEachTileOf(TILES &tiles)
            {
                const size_t numTiles     = tiles.size(); assert(numTiles>0);
                const size_t bytesPerTile = blockSize / numTiles;
                if(bytesPerTile>0)
                {
                    uint8_t * entryPerTile = static_cast<uint8_t *>(blockAddr);
                    for(size_t i=1;i<=numTiles;++i, entryPerTile += bytesPerTile)
                    {
                        Coerce(tiles[i].entry) = entryPerTile;
                        Coerce(tiles[i].bytes) = bytesPerTile;
                    }
                }
                else
                    clearEachTileOf(tiles);
            }

            

        public:
            const size_t blockSize; //!< total allocated bytes
            void * const blockAddr; //!< memory

        private:
            Y_Disable_Copy_And_Assign(Resources); //!< discarding
            void release() noexcept;              //!< release total memory
            void ensure(size_t capacity);         //!< \param capacity minimal, zeroed bytes

            //! mark each tile as free \param tiles collection of tiles
            template <typename TILES> inline
            void clearEachTileOf(TILES &tiles) noexcept
            {
                for(size_t i=tiles.size();i>0;--i)
                {
                    Coerce(tiles[i].entry) = 0;
                    Coerce(tiles[i].bytes) = 0;
                }
            }
        };
    }
}

#endif // !Y_Concurrent_Resources_Included

