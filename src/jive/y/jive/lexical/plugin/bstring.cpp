#include "y/jive/lexical/plugin/bstring.hpp"

namespace Yttrium
{
    namespace Jive
    {

        namespace Lexical
        {
            const char BString:: JOIN;
            const char BString:: QUIT;

            Y_Jive_Plugin_Impl(BString);

            void BString:: finalize()
            {
                send("dquote", '\"');
                send("quote",  '\'');
            }

            
        }

    }

}

