
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

            
            void Plugin:: onCall(const Token &token)
            {
                data.free();
                data << token;
            }

            void Plugin:: onBack(const Token &leave)
            {
                data << leave;
                if(data.size<=0)
                    throw Specific::Exception(name->c_str(),"no collected data");
                const Context ctx = *data.head;
                root.store( new Unit(name,ctx,data) );
            }

        }
    }
}

