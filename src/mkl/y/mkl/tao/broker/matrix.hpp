

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

            typedef Concurrent::Divide::Tile2D<size_t>     Tile2D;       //!< alias
            typedef Concurrent::Divide::Tiles2D<size_t>    Tiles2D;      //!< alias
            typedef Concurrent::Spawn<Tiles2D>             MatrixSpawn;  //!< alias
            typedef MatrixSpawn::Pointer                   MatrixEngine; //!< alias
            typedef V2D<size_t>                            MatrixVertex;
            typedef Concurrent::Divide::Box<MatrixVertex>  MatrixBox;
            
            //__________________________________________________________________
            //
            //
            //
            //! will split operations on matrices
            //
            //
            //__________________________________________________________________
            template <typename T>
            class MatrixBroker : public Ingress< MatrixSpawn >
            {
            public:
                //______________________________________________________________
                //
                //
                // definitions
                //
                //______________________________________________________________
                typedef Cameo::Addition<T> XAddition; //!< alias


                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup from shared linear spawn \param eng shared engine
                inline explicit MatrixBroker(const MatrixEngine &eng) :
                engine(eng),
                caddy()
                {
                    engine->link( caddy.adjust(engine->size()).head );
                }

                //! cleanup
                inline virtual ~MatrixBroker() noexcept {}

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________


                //! \return first XAddition
                inline XAddition & xadd() noexcept
                {
                    assert( caddy.head );
                    return *caddy.head;
                }

                

            private:
                Y_Disable_Copy_And_Assign(MatrixBroker); //!< disable

                inline virtual ConstInterface & locus() const noexcept { return *engine; }

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                MatrixEngine     engine; //!< shared engine
                Cameo::Caddy<T>  caddy;  //!< xadditions
            };

        }

    }
}

#endif // !Y_MKL_Tao_MatrixBroker_Included

