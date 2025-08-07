
#include "y/jive/lexical/comment.hpp"

namespace Yttrium
{
    namespace Jive
    {

        namespace Lexical
        {
            Comment:: ~Comment() noexcept
            {

            }


            void Comment:: finalize()
            {
                decl("dot", ".", Regular, false);
            }

        }

    }

}
