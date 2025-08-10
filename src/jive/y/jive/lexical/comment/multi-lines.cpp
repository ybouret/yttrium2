

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
                decl("endl", "[:endl:]", NewLine, DropToken);
                finalize();
            }


            size_t MultiLinesComment:: serialize(OutputStream &fp) const
            {
                size_t res = emitUUID(fp);
                res += join->serialize(fp);
                res += quit->serialize(fp);
                return res;
            }
        }

    }

}
