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

            //! release all memory \param tiles updated tiles
            template <typename TILES> inline
            void releaseEachTileOf(TILES &tiles) noexcept
            {
                for(size_t i=tiles.size();i>0;--i)
                {
                    Coerce(tiles[i].entry) = 0;
                    Coerce(tiles[i].bytes) = 0;
                }
                release();
            }


        public:
            const size_t blockSize; //!< total allocated bytes
            void * const blockAddr; //!< memory

        private:
            Y_Disable_Copy_And_Assign(Resources); //!< discarding
            void release() noexcept;              //!< release total memory
            void ensure(size_t capacity);         //!< \param capacity minimal, zeroed bytes
        };
    }
}

#endif // !Y_Concurrent_Resources_Included

