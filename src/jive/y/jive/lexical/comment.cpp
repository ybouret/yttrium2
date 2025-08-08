
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


            void Comment:: onCall(const Token &)
            {

            }

            void Comment:: onBack(const Token &)
            {
                
            }

            void Comment:: onSent(const Token &)
            {
                forbidden("Comment::onSent");
            }

        }

    }

}
