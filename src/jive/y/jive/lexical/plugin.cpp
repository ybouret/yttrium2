
#include "y/jive/lexical/plugin.hpp"
#include "y/jive/lexer.hpp"
#include "y/exception.hpp"

namespace Yttrium
{
    namespace Jive
    {

        namespace Lexical
        {
            Plugin:: ~Plugin() noexcept
            {

            }

            
            void Plugin:: onCall(Token &token)
            {
                data.free();
                data.mergeTail(token);
            }

            void Plugin:: onBack(Token &leave)
            {
                data.mergeTail(leave);
                if(data.size<=0)
                    throw Specific::Exception(name->c_str(),"no collected data");
                const Context ctx = *data.head;
                root.store( new Unit(name,ctx,data) );
            }

        }
    }
}

