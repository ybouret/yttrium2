
#include "y/jive/lexical/comment/single-line.hpp"

namespace Yttrium
{
    namespace Jive
    {

        namespace Lexical
        {
            SingleLineComment:: ~SingleLineComment() noexcept
            {

            }

            void SingleLineComment:: setup()
            {
                back("[:endl:]", NewLine);
                finalize();
            }

        }

    }

}
