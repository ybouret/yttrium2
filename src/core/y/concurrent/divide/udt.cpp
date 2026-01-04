
#include "y/concurrent/divide/udt.hpp"

namespace Yttrium
{
    namespace Concurrent
    {
        namespace Divide
        {

            UpperDiagonalTile:: ~UpperDiagonalTile() noexcept
            {
            }

            UpperDiagonalTile:: UpperDiagonalTile(const size_t  mySize,
                                                  const size_t  myRank,
                                                  const size_t  extent) :
            Subdivision(mySize,myRank),
            n(extent),
            kNumber( (n *(n+1)) >> 1),
            kOffset(1),
            kLength( part<size_t>(kNumber, Coerce(kOffset) ) ),
            kUtmost( kOffset + kLength - 1 )
            {
                
            }


        }
    }
}


