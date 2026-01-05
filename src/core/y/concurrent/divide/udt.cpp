
#include "y/concurrent/divide/udt.hpp"
#include "y/calculus/isqrt.hpp"
#include "y/calculus/alignment.hpp"

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
            B(1+(n<<1)),
            kNumber( (n *(n+1)) >> 1),
            kOffset(1),
            kLength( part<size_t>(kNumber, Coerce(kOffset) ) ),
            kUtmost( kOffset + kLength - 1 )
            {
                
            }


            size_t UpperDiagonalTile:: getI(const size_t k) const noexcept
            {
                assert(k>=1);
                assert(k<=kNumber);
                const size_t Delta = B*B - (k<<3);
                const size_t twice = (B - IntegerSquareRoot(Delta));
                const size_t align = Alignment::On<2>::Ceil(twice);
                return align>>1;
            }

        }
    }
}


