

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
            template <typename T, typename SPAWN>
            class BrokerProto : public BrokerBasis<T>, public Ingress<SPAWN>
            {
            public:
                typedef BrokerBasis<T>                       BrokerType;
                typedef typename SPAWN::Pointer              EngineType;
                typedef Ingress<SPAWN>                       IngressType;
                typedef typename IngressType::ConstInterface ConstInterface;
                using BrokerType::caddy;

                inline explicit BrokerProto(const EngineType eng) :
                BrokerType(eng->size()),
                IngressType(),
                engine(eng)
                {
                    engine->link(caddy.head);
                }

                inline virtual ~BrokerProto() noexcept {}


            private:
                Y_Disable_Copy_And_Assign(BrokerProto);
                inline virtual ConstInterface & locus() const noexcept { return *engine; }

                EngineType engine;
            };
        }

    }

}

#endif // !Y_MKL_Tao_BrokerProto_Included
