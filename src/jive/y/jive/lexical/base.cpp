
#include "y/jive/lexical/base.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Lexical
        {

            Base:: ~Base() noexcept
            {

            }

            Base:: Base() : pdb( new Dictionary() ), nil() {}


            Base:: Base(const Base &_) noexcept : pdb(_.pdb), nil(_.nil) {}
        }

    }

}
