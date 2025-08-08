#include "y/jive/lexical/plugin/strings.hpp"

namespace Yttrium
{
    namespace Jive
    {

        namespace Lexical
        {
            Strings:: ~Strings() noexcept {}

            void Strings:: initialize()
            {
                decl("core","[:core:]",Regular,SendToken);
            }

            void Strings:: onSent(Token &token)
            {
                data.mergeTail(token);
            }
        }
    }

}
