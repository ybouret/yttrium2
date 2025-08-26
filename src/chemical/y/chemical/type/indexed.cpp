
#include "y/chemical/type/indexed.hpp"
#include <cstring>

namespace Yttrium
{
    namespace Chemical
    {

        Indexed:: ~Indexed() noexcept
        {
            memset( Coerce(indx), 0, sizeof(indx) );
        }

        void Indexed:: setup(const size_t top) noexcept
        {
            assert(top>0);
            memset( Coerce(indx), 0, sizeof(indx) );
            Coerce(indx[TopLevel]) = top;
        }

        Indexed:: Indexed(const size_t top) : Entity(), indx()
        {
            setup(top);
        }

    }
    
    
}
