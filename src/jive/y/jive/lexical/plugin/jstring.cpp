
#include "y/jive/lexical/plugin/jstring.hpp"

namespace Yttrium
{
    namespace Jive
    {

        namespace Lexical
        {
            const char JString:: JOIN;

            Y_Jive_Plugin_Impl(JString);

            void JString:: finalize()
            {
                decl("quote", '\'', Regular, SendToken);
            }
        }

    }

}
