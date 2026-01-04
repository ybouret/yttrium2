
//! \file


#ifndef Y_Concurrent_Divide_UDT_Included
#define Y_Concurrent_Divide_UDT_Included 1

#include "y/concurrent/member.hpp"
#include "y/concurrent/type/subdivision.hpp"

namespace Yttrium
{
    namespace Concurrent
    {
        namespace Divide
        {

            class UpperDiagonalTile : public Subdivision
            {
            public:

                //! UpperDiagonal of a extent x extent matrix
                /**
                 \param mySize size of the group
                 \param myRank rank in the group
                 \param extent extent
                 */
                explicit UpperDiagonalTile(const size_t  mySize,
                                           const size_t  myRank,
                                           const size_t  extent);

                virtual ~UpperDiagonalTile() noexcept;

                size_t getI(const size_t k);

                const size_t n;        //!< n x n array
                const size_t B;        //!< 1 + 2*n*
                const size_t kNumber;  //!< n*(n+1)/2
                const size_t kOffset;  //!< initial k
                const size_t kLength;  //!< number of indices
                const size_t kUtmost;  //!< utmost  k

            private:
                Y_Disable_Copy_And_Assign(UpperDiagonalTile);
            };

        }

    }

}

#endif // !Y_Concurrent_Divide_UDT_Included

