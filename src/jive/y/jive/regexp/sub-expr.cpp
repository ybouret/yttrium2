
#include "y/jive/regexp/compiler.hpp"
#include "y/jive/pattern/all.hpp"
#include "y/pointer/auto.hpp"
#include "y/system/exception.hpp"

namespace Yttrium
{
    namespace Jive
    {

        Pattern * RegExp::Compiler:: subExpr()
        {
            AutoPtr<Logic> motif = new And();
            Logic         &p     = *motif;
            while(curr<last)
            {
                const char C = *(curr++);

                switch(C)
                {

                    default:
                        p << new Single(C);
                }
            }

            if(p->size<=0)
                throw Specific::Exception(CallSign,"empty sub-expression in '%s'", expr);

            return motif.yield();
        }

    }

}
