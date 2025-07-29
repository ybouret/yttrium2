#include "y/apex/api/coven/tribes.hpp"


namespace Yttrium
{

    namespace Coven
    {

        void Tribes:: makeEndEarlyBasis() noexcept
        {

            Tribe::List list;
            while(size>0)
            {
                if( Apex::Ortho::Basis == head->family->quality )
                {
                    delete popHead();
                }
                else
                {
                    list.pushTail( popHead() );
                }
            }
            swapListFor(list);
        }
    }

}

