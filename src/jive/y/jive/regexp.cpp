
#include "y/jive/regexp.hpp"
#include "y/jive/regexp/compiler.hpp"
#include "y/pointer/auto.hpp"
#include "y/system/exception.hpp"
#include "y/jive/pattern/basic/byte.hpp"

namespace Yttrium
{
    namespace Jive
    {
        Pattern * RegExp:: Compile(const char *const expr, const Dictionary * const dict)
        {
            const String _(expr);
            return Compile(_,dict);
        }


        Pattern * RegExp:: Compile(const String &expr, const Dictionary * const dict)
        {
            Compiler         compiler(expr,dict);
            AutoPtr<Pattern> motif = compiler.subExpr();
            if(compiler.deep>0) throw Specific::Exception(Compiler::CallSign,"unfinished '%s'",compiler.expr);
            return Pattern::Optimize( motif.yield() );
        }

        Pattern * RegExp:: Compile(const char C, const Dictionary * const)
        {
            return new Byte(C);
        }
    }

}
