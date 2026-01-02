

//! \file

#ifndef Y_MKL_Tao_BrokerProto_Included
#define Y_MKL_Tao_BrokerProto_Included 1

#include "y/mkl/tao/broker/basis.hpp"

namespace Yttrium
{

    namespace MKL
    {

        namespace Tao
        {
            //__________________________________________________________________
            //
            //
            //
            //! manage Concurrent Spawn and Cameo additions
            //
            //
            //__________________________________________________________________
            template <typename T, typename SPAWN>
            class BrokerProto : public BrokerBasis<T>, public Ingress<SPAWN>
            {
            public:
                //______________________________________________________________
                //
                //
                // definitions
                //
                //______________________________________________________________
                typedef BrokerBasis<T>                       BrokerType;      //!< alias
                typedef typename SPAWN::Pointer              EngineType;      //!< alias
                typedef Ingress<SPAWN>                       IngressType;     //!< alias
                typedef typename IngressType::ConstInterface ConstInterface;  //!< alias
                using BrokerType::caddy;

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup \param eng shared concurrent engine
                inline explicit BrokerProto(const EngineType &eng) :
                BrokerType(eng->size()),
                IngressType(),
                engine(eng)
                {
                    engine->link(caddy.head);
                }

                //! cleanup
                inline virtual ~BrokerProto() noexcept {}

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
            protected:
                EngineType engine; //!< shared engine/spawn

            private:
                Y_Disable_Copy_And_Assign(BrokerProto); //!< discarding
                inline virtual ConstInterface & locus() const noexcept { return *engine; }


            };
        }

    }

}

#endif // !Y_MKL_Tao_BrokerProto_Included
