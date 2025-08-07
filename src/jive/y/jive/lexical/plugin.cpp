
#include "y/jive/lexical/plugin.hpp"
#include "y/jive/lexer.hpp"
#include "y/system/exception.hpp"

namespace Yttrium
{
    namespace Jive
    {

        namespace Lexical
        {
            Plugin:: ~Plugin() noexcept
            {

            }

            void Plugin:: yield()
            {
                if(data.size<=0) throw Specific::Exception(name->c_str(),"not collected data");
                const Context ctx = *data.head;
                root.store( new Unit(name,ctx,data) );
            }

        }
    }
}

