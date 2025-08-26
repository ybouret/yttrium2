
#include "y/chemical/reactive/actors.hpp"


namespace Yttrium
{
    namespace Chemical
    {
        Actors:: ~Actors() noexcept
        {
        }

        Actors:: Actors( const Actor::Role r) :
        list(),
        role(r)
        {
        }

        Y_Ingress_Impl(Actors,list)
        
    }

}

