#include "y/jive/lexical/plugin/rstring.hpp"

namespace Yttrium
{
    namespace Jive
    {

        namespace Lexical
        {
            const char RString:: JOIN;

            Y_Jive_Plugin_Impl(RString);

            void RString:: finalize()
            {
                send("dquote", '\"');
            }


        }

    }

}
