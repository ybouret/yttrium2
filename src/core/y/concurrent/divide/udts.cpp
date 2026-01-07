
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

            UpperDiagonalTiles:: UpperDiagonalTiles(const size_t threads,
                                                    const size_t metrics) :
            Writable<UpperDiagonalTile>(),
            tiles(threads)
            {
                for(size_t i=0;i<threads;++i) tiles.push(threads,i,metrics);
            }

            UpperDiagonalTiles:: UpperDiagonalTiles(const size_t threads) :
            Writable<UpperDiagonalTile>(),
            tiles(threads)
            {
                const size_t n = 0;
                for(size_t i=0;i<threads;++i) tiles.push(threads,i,n);
            }

            size_t UpperDiagonalTiles:: size() const noexcept { return tiles.size(); }

            const UpperDiagonalTile & UpperDiagonalTiles:: getItemAt(const size_t i) const noexcept
            {
                assert(i>=1); assert(i<=tiles.size());
                return tiles[i];
            }

        }

    }

}
