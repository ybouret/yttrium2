


//! \file

#ifndef Y_MKL_Tao_UpperDiagonalBroker_Included
#define Y_MKL_Tao_UpperDiagonalBroker_Included 1

#include "y/mkl/tao/broker/proto.hpp"
#include "y/concurrent/divide/udts.hpp"
#include "y/concurrent/api/simd/spawn.hpp"
#include "y/cameo/caddy.hpp"

namespace Yttrium
{

    namespace MKL
    {

        namespace Tao
        {

            typedef Concurrent::Divide::UpperDiagonalTile  UpperDiagonalTile;        //!< alias
            typedef Concurrent::Divide::UpperDiagonalTiles UpperDiagonalTiles;       //!< alias
            typedef Concurrent::Spawn<UpperDiagonalTiles>  UpperDiagonalSpawn;   //!< alias
            typedef UpperDiagonalSpawn::Pointer            UpperDiagonalEngine;  //!< alias
            //typedef V2D<size_t>                            MatrixVertex;  //!< alias
            //typedef Concurrent::Divide::Box<MatrixVertex>  MatrixBox;     //!< alias
            //typedef Concurrent::Divide::HSegment<size_t>   MatrixSegment; //!< alias

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

#if 0
                //! prepare tiles \param a using (1,1) -> (a.cols,a.rows)
                inline void prep(const MatrixMetrics &a)
                {
                    const MatrixVertex lo(1,1);
                    const MatrixVertex up(a.cols,a.rows);
                    const MatrixBox    box(lo,up);
                    if(engine->remap(box))
                        engine->link(caddy.head);
                }
#endif


            private:
                Y_Disable_Copy_And_Assign(UpperDiagonalBroker); //!< discarding
            };

        }

    }
}

#endif // !Y_MKL_Tao_UpperDiagonalBroker_Included

