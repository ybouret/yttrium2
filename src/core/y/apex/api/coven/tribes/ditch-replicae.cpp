
#include "y/apex/api/coven/tribes.hpp"


namespace Yttrium
{

    namespace Coven
    {
        void Tribes:: makeDitchReplicae() noexcept
        {

            if(size<=1) return;

            Tribe::List target;
            target.pushTail( popHead() );
            while(size>0)
            {
                Tribe &lhs = *target.tail;
                Tribe &rhs = *head;

                if( (lhs.basis==rhs.basis) && (lhs.ready == rhs.ready) )
                {
                    delete popHead();
                    continue;
                }

                target.pushTail( popHead() );
            }
            swapListFor(target);

            
        }
    }

}

