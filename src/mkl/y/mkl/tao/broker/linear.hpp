
//! \file

#ifndef Y_MKL_Tao_LinearBroker_Included
#define Y_MKL_Tao_LinearBroker_Included 1

#include "y/concurrent/divide/1d.hpp"
#include "y/concurrent/api/simd/spawn.hpp"
#include "y/mkl/tao/broker/proto.hpp"

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
            class LinearBroker : public BrokerProto<T,LinearSpawn>
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                typedef BrokerProto<T,LinearSpawn> Prototype; //!< alias

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup \param eng shared engine
                inline explicit LinearBroker(const LinearEngine &eng) :
                Prototype(eng)
                {
                }

                //! cleanup
                inline virtual ~LinearBroker() noexcept {}

            private:
                Y_Disable_Copy_And_Assign(LinearBroker); //!< discarding
            };


        }

    }
}

#endif // !Y_MKL_Tao_LinearBroker_Included

