

#include "y/jive/lexical/comment/multi-lines.hpp"

namespace Yttrium
{
    namespace Jive
    {

        namespace Lexical
        {
            MultiLinesComment:: ~MultiLinesComment() noexcept
            {

            }

            void MultiLinesComment:: setup()
            {
                decl("endl", "[:endl:]", NewLine, false);
                finalize();
            }

        }

    }

}
