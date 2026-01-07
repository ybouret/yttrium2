
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
            B2(B*B),
            kNumber( (n *(n+1)) >> 1),
            kOffset(1),
            kLength( part<size_t>(kNumber, Coerce(kOffset) ) ),
            kUtmost( kOffset + kLength - 1 )
            {
                setup();
            }

            bool UpperDiagonalTile:: isEmpty() const noexcept
            {
                return kLength <= 0;
            }

            size_t UpperDiagonalTile:: getI(const size_t k) const noexcept
            {
                assert(k>=1);
                assert(k<=kNumber);
                const size_t Delta = B2 - (k<<3);
                const size_t twice = (B - IntegerSquareRoot(Delta));
                const size_t align = Alignment::On<2>::Ceil(twice);
                return align>>1;
            }

            size_t UpperDiagonalTile:: getK(const size_t i) const noexcept
            {
                return i * n - (((i-1)*i)>>1);
            }

            size_t UpperDiagonalTile:: getJ(const size_t k, const size_t i) const noexcept
            {
                const size_t im1 = i-1;
                return im1 + k-getK(im1);
            }

            MatrixCoord UpperDiagonalTile:: operator()(const size_t k) const noexcept
            {
                const size_t i = getI(k);
                return MatrixCoord(i,getJ(k,i));
            }

            void UpperDiagonalTile:: setup()
            {
                if(kLength<=0) return;
                const MatrixCoord ini = (*this)(kOffset);
                const MatrixCoord end = (*this)(kUtmost);
                std::cerr << "ini=" << ini << ", end=" << end << std::endl;
            }
        }
    }
}


