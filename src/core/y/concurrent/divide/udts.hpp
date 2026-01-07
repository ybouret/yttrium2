
#ifndef Y_Concurrent_Divide_UDTS_Included
#define Y_Concurrent_Divide_UDTS_Included 1


#include "y/concurrent/divide/udt.hpp"
#include "y/container/cxx/series.hpp"

namespace Yttrium
{

    namespace Concurrent
    {
        namespace Divide
        {

            class UpperDiagonalTiles : public Writable< UpperDiagonalTile >
            {
            public:
                //! prepare tiles
                /**
                 \param threads given number of threads
                 \param metrics given square matrix metrics
                 */
                explicit UpperDiagonalTiles(const size_t threads,
                                            const size_t metrics);

                //! prepare empty tiles
                /**
                 \param threads given number of threads
                 */
                explicit UpperDiagonalTiles(const size_t threads);

                //! cleanup
                virtual ~UpperDiagonalTiles() noexcept;

                virtual size_t size() const noexcept;

            private:
                CxxSeries<UpperDiagonalTile> tiles;
                Y_Disable_Copy_And_Assign(UpperDiagonalTiles);

                virtual const UpperDiagonalTile & getItemAt(const size_t) const noexcept;
                
            };

        }

    }

}

#endif // !Y_Concurrent_Divide_UDTS_Included
