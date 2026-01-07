
//! \file


#ifndef Y_Concurrent_Divide_UDT_Included
#define Y_Concurrent_Divide_UDT_Included 1

#include "y/concurrent/member.hpp"
#include "y/concurrent/type/subdivision.hpp"
#include "y/container/matrix/coord.hpp"
#include "y/concurrent/divide/hsegment.hpp"

namespace Yttrium
{
    
    namespace Concurrent
    {
        namespace Divide
        {

            //_________________________________________________________________
            //
            //
            //
            //! tile of an upper diagonal matrix
            //
            //
            //__________________________________________________________________
            class UpperDiagonalTile : public Subdivision
            {
            public:

                //! UpperDiagonal of a extent x extent matrix
                /**
                 \param mySize size of the group
                 \param myRank rank in the group
                 \param extent extent is the size of the matrix
                 */
                explicit UpperDiagonalTile(const size_t  mySize,
                                           const size_t  myRank,
                                           const size_t  extent);

                virtual ~UpperDiagonalTile() noexcept;

                virtual bool isEmpty() const noexcept;

                size_t getI(const size_t k) const noexcept;                 //!< \param k valid index \return row index from k
                size_t getK(const size_t i) const noexcept;                 //!< \param i row index   \return max k for i-th row
                size_t getJ(const size_t k, const size_t i) const noexcept; //!< \param k valid indx \param i matching row index \return column index

                //! \param k valid index \return associated matrix coordinates
                MatrixCoord operator()(const size_t k) const noexcept;


                const size_t n;        //!< n x n array
                const size_t B;        //!< 1 + 2*n*
                const size_t B2;       //!< B^2
                const size_t kNumber;  //!< n*(n+1)/2
                const size_t kOffset;  //!< initial valid k
                const size_t kLength;  //!< number of indices, 0 meanms empty
                const size_t kUtmost;  //!< utmost  valid k

            private:
                Y_Disable_Copy_And_Assign(UpperDiagonalTile); //!< discarding
                void setup();
            };

        }

    }

}

#endif // !Y_Concurrent_Divide_UDT_Included

