
#include "y/apex/api/coven/tribes.hpp"


namespace Yttrium
{

    namespace Coven
    {
        void Tribes:: makeDitchReplicae()
        {
            std::cerr << "DitchReplicae :" <<  size << " => ";
            Tribe::List target;
            while(size>0)
            {
                if(target.size<=0)
                {
                    target.pushTail( popHead() );
                    continue;
                }

                assert(target.tail!=0);
                Tribe &lhs = *target.tail;
                Tribe &rhs = *head;

                if(lhs.basis==rhs.basis && lhs.ready == rhs.ready)
                {
                    delete popHead();
                    continue;
                }

                target.pushTail( popHead() );
            }

            swapListFor(target);
            std::cerr << size << std::endl;

        }
    }

}

