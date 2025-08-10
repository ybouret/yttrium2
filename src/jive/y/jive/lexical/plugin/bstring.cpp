#include "y/jive/lexical/plugin/bstring.hpp"
#include "y/stream/output.hpp"

namespace Yttrium
{
    namespace Jive
    {

        namespace Lexical
        {
            const char BString:: JOIN;
            const char BString:: QUIT;

            Y_Jive_Plugin_Impl(BString);

            void BString:: finalize()
            {
                send("dquote", '\"');
                send("quote",  '\'');
            }

            size_t BString:: serialize(OutputStream &fp) const
            {
                const size_t res = emitUUID(fp);
                fp.write(JOIN);
                fp.write(QUIT);
                return res+2;
            }
        }

    }

}

