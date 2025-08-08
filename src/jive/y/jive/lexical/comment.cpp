
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
                drop("dot", ".");
            }


            void Comment:: onCall(Token &)
            {

            }

            void Comment:: onBack(Token &)
            {
                
            }

            void Comment:: onSent(Token &token)
            {
                forbidden("Comment::onSent",token);
            }

        }

    }

}
