

//! \file

#ifndef Y_MKL_Tao_MatrixBroker_Included
#define Y_MKL_Tao_MatrixBroker_Included 1

#include "y/concurrent/divide/2d.hpp"
#include "y/concurrent/api/simd/spawn.hpp"
#include "y/cameo/caddy.hpp"

namespace Yttrium
{

    namespace MKL
    {

        namespace Tao
        {

            typedef Concurrent::Divide::Tile2D<size_t>     Tile2D;        //!< alias
            typedef Concurrent::Divide::Tiles2D<size_t>    Tiles2D;       //!< alias
            typedef Concurrent::Spawn<Tiles2D>             MatrixSpawn;   //!< alias
            typedef MatrixSpawn::Pointer                   MatrixEngine;  //!< alias
            typedef V2D<size_t>                            MatrixVertex;  //!< alias
            typedef Concurrent::Divide::Box<MatrixVertex>  MatrixBox;     //!< alias
            typedef Concurrent::Divide::HSegment<size_t>   MatrixSegment; //!< alias

            //__________________________________________________________________
            //
            //
            //
            //! will split operations on matrices
            //
            //
            //__________________________________________________________________
            template <typename T>
            class MatrixBroker : public BrokerProto<T,MatrixSpawn>
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                typedef BrokerProto<T,MatrixSpawn> Prototype;
                using Prototype::engine;
                using Prototype::caddy;
                
                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                inline explicit MatrixBroker(const MatrixEngine &eng) :
                Prototype(eng)
                {
                }


                inline virtual ~MatrixBroker() noexcept
                {
                }

                inline void prep(const MatrixMetrics &a)
                {
                    const MatrixVertex lo(1,1);
                    const MatrixVertex up(a.rows,a.cols);
                    const MatrixBox    box(lo,up);
                    engine->remap(box);
                    engine->link(caddy.head);
                }



            private:
                Y_Disable_Copy_And_Assign(MatrixBroker); //!< discarding
            };

            
        }

    }
}

#endif // !Y_MKL_Tao_MatrixBroker_Included

