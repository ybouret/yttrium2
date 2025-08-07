
#include "y/jive/lexical/design.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Lexical
        {

            Design:: ~Design() noexcept
            {

            }

            Design:: Design() : pdb( new Dictionary() ), nil() {}


            Design:: Design(const Design &_) noexcept : pdb(_.pdb), nil(_.nil) {}
        }

    }

}
