
#include "y/jive/regexp/compiler.hpp"

namespace Yttrium
{
    namespace Jive
    {
        RegExp:: Compiler:: ~Compiler() noexcept
        {

        }

        const char * const RegExp:: Compiler:: CallSign = "Jive::RegExp";

        RegExp:: Compiler:: Compiler(const String &userExpr, const Dictionary * const userDict) noexcept :
        curr( userExpr.c_str() ),
        last( curr+userExpr.size() ),
        deep(0),
        expr( curr ),
        dict( userDict )
        {
            
        }




    }

}
