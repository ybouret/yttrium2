
#include "y/concurrent/divide/udts.hpp"

namespace Yttrium
{

    namespace Concurrent
    {
        namespace Divide
        {
            UpperDiagonalTiles:: ~UpperDiagonalTiles() noexcept
            {
                
            }

            void UpperDiagonalTiles:: buildFor(const size_t threads)
            {
                for(size_t i=0;i<threads;++i) tiles.push(threads,i,realm);
            }

            UpperDiagonalTiles:: UpperDiagonalTiles(const size_t threads,
                                                    const size_t metrics) :
            Writable<UpperDiagonalTile>(),
            tiles(threads),
            realm(metrics)
            {
                buildFor(threads);
            }

            UpperDiagonalTiles:: UpperDiagonalTiles(const size_t threads) :
            Writable<UpperDiagonalTile>(),
            tiles(threads),
            realm(0)
            {
                buildFor(threads);
            }

            size_t UpperDiagonalTiles:: size() const noexcept { return tiles.size(); }

            const UpperDiagonalTile & UpperDiagonalTiles:: getItemAt(const size_t i) const noexcept
            {
                assert(i>=1); assert(i<=tiles.size());
                return tiles[i];
            }


            void UpperDiagonalTiles:: remap(const size_t metrics)
            {
                UpperDiagonalTiles udts(tiles.size(),metrics); assert( size() == udts.size() );

                tiles.xch(udts.tiles);
                CoerceSwap(realm,udts.realm);
                
            }

        }

    }

}
