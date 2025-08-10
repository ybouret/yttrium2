#include "y/jive/lexical/plugin/rstring.hpp"
#include "y/stream/output.hpp"

namespace Yttrium
{
    namespace Jive
    {

        namespace Lexical
        {
            const char RString:: JOIN;

            Y_Jive_Plugin_Impl(RString);

            void RString:: finalize()
            {
                send("dquote", '\"');
            }

            size_t RString:: serialize(OutputStream &fp) const
            {
                const size_t res = emitUUID(fp);
                fp.write(JOIN);
                return res+1;
            }
        }

    }

}
