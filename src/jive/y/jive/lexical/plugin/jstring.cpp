
#include "y/jive/lexical/plugin/jstring.hpp"
#include "y/stream/output.hpp"

namespace Yttrium
{
    namespace Jive
    {

        namespace Lexical
        {
            const char JString:: JOIN;

            Y_Jive_Plugin_Impl(JString);

            void JString:: finalize()
            {
                send("quote", '\'');
            }

            size_t JString:: serialize(OutputStream &fp) const
            {
                const size_t res = emitUUID(fp);
                fp.write(JOIN);
                return res+1;
            }
        }

    }

}
