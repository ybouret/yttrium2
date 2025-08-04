
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

                    case LPAREN:
                        ++deep;
                        p << subExpr();
                        break;

                    case RPAREN:
                        if(deep<=0) throw Specific::Exception(CallSign,"extraneous '%c' in '%s'",RPAREN,expr);
                        --deep;
                        goto RETURN;

                    default:
                        p << new Single(C);
                }
            }

        RETURN:
            if(p->size<=0)
                throw Specific::Exception(CallSign,"empty sub-expression in '%s'", expr);

            return motif.yield();
        }

    }

}
