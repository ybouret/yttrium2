
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
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                typedef UpperDiagonalTile Tile;       //!< alias
                typedef size_t            Parameter;  //!< alias for Spawn

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
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

                //______________________________________________________________
                //
                //
                // Interface
                //
                //______________________________________________________________
                virtual size_t size() const noexcept;

            private:
                virtual const UpperDiagonalTile & getItemAt(const size_t) const noexcept;
                Y_Disable_Copy_And_Assign(UpperDiagonalTiles); //!< discarding

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________
                void buildFor(const size_t threads); //!< setup \param threads number of tiles sharing realm

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                CxxSeries<UpperDiagonalTile> tiles; //!< series of tiles
                const size_t                 realm; //!< currently mapped
            };

        }

    }

}

#endif // !Y_Concurrent_Divide_UDTS_Included
