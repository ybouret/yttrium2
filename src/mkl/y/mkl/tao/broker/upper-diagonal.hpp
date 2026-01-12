


//! \file

#ifndef Y_MKL_Tao_UpperDiagonalBroker_Included
#define Y_MKL_Tao_UpperDiagonalBroker_Included 1

#include "y/mkl/tao/broker/proto.hpp"
#include "y/concurrent/divide/udts.hpp"
#include "y/concurrent/api/simd/spawn.hpp"
#include "y/cameo/caddy.hpp"
#include "y/container/matrix/metrics.hpp"

namespace Yttrium
{

    namespace MKL
    {

        namespace Tao
        {

            typedef Concurrent::Divide::UpperDiagonalTile    UpperDiagonalTile;    //!< alias
            typedef Concurrent::Divide::UpperDiagonalTiles   UpperDiagonalTiles;   //!< alias
            typedef Concurrent::Spawn<UpperDiagonalTiles>    UpperDiagonalSpawn;   //!< alias
            typedef UpperDiagonalSpawn::Pointer              UpperDiagonalEngine;  //!< alias
            typedef Concurrent::Divide::UpperDiagonalSegment UpperDiagonalSegment; //!< alias

            //__________________________________________________________________
            //
            //
            //
            //! will split operations on matrices
            //
            //
            //__________________________________________________________________
            template <typename T>
            class UpperDiagonalBroker : public BrokerProto<T,UpperDiagonalSpawn>
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                typedef BrokerProto<T,UpperDiagonalSpawn> Prototype; //!< alias
                using Prototype::engine;
                using Prototype::caddy;

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup \param eng shared engine
                inline explicit UpperDiagonalBroker(const UpperDiagonalEngine &eng) :
                Prototype(eng)
                {
                }

                //! cleanup
                inline virtual ~UpperDiagonalBroker() noexcept
                {
                }

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________

                //! prepare tiles \param a using (1,1) -> (a.cols,a.rows)
                inline void prep(const MatrixMetrics &a)
                {
                    assert(a.isSquare());
                    const size_t n = a.rows;
                    if(engine->remap(n))
                        engine->link(caddy.head);
                }


            private:
                Y_Disable_Copy_And_Assign(UpperDiagonalBroker); //!< discarding
            };

        }

    }
}

#endif // !Y_MKL_Tao_UpperDiagonalBroker_Included

