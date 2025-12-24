
//! \file

#ifndef Y_MKL_Tao_LinearBroker_Included
#define Y_MKL_Tao_LinearBroker_Included 1

#include "y/concurrent/divide/1d.hpp"
#include "y/concurrent/api/simd/spawn.hpp"
#include "y/cameo/caddy.hpp"

namespace Yttrium
{

    namespace MKL
    {

        namespace Tao
        {

            typedef Concurrent::Divide::Tile1D<size_t>     Tile1D;       //!< alias
            typedef Concurrent::Divide::CxxTiles1D<size_t> Tiles1D;      //!< alias
            typedef Concurrent::Spawn<Tiles1D>             LinearSpawn;  //!< alias
            typedef LinearSpawn::Pointer                   LinearEngine; //!< alias

            //__________________________________________________________________
            //
            //
            //
            //! will split operations on matrix rows/cols
            //
            //
            //__________________________________________________________________
            template <typename T>
            class LinearBroker : public Ingress< LinearSpawn >
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
                inline explicit LinearBroker(const LinearEngine &eng) :
                engine(eng),
                caddy()
                {
                    engine->link( caddy.adjust(engine->size()).head );
                }

                //! cleanup
                inline virtual ~LinearBroker() noexcept {}

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________

                /*
                 inline void relink() noexcept
                 {
                 engine->link( caddy.head );
                 }
                 */

                //! \return first XAddition
                inline XAddition & xadd() noexcept
                {
                    assert( caddy.head );
                    return *caddy.head;
                }


            private:
                Y_Disable_Copy_And_Assign(LinearBroker); //!< disable

                inline virtual ConstInterface & locus() const noexcept { return *engine; }

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                LinearEngine     engine; //!< shared engine
                Cameo::Caddy<T>  caddy;  //!< xadditions
            };

        }

    }
}

#endif // !Y_MKL_Tao_LinearBroker_Included

