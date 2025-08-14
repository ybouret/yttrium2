
#include "y/jive/syntax/rule/wildcard.hpp"
//#include "y/stream/output.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Syntax
        {

            Wildcard:: ~Wildcard() noexcept
            {
            }

            OutputStream & Wildcard:: vizPost(OutputStream &fp) const
            {
                return Endl( to( &rule,fp) );
            }

        }

    }

}

