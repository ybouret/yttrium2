
#include "y/jive/lexical/comment/single-line.hpp"
//#include "y/stream/output.hpp"

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


            size_t SingleLineComment:: serialize(OutputStream &fp) const
            {
                size_t res = emitUUID(fp);
                return res + join->serialize(fp);
            }

        }

    }

}
