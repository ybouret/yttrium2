
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
            while(curr<last)
            {
                const char C = *(curr++);

                switch(C)
                {
                        //------------------------------------------------------
                        //
                        // grouping
                        //
                        //------------------------------------------------------
                    case LPAREN:
                        ++deep;
                        *motif << subExpr();
                        break;

                    case RPAREN:
                        if(deep<=0) throw Specific::Exception(CallSign,"extraneous '%c' in '%s'",RPAREN,expr);
                        --deep;
                        goto RETURN;

                        //------------------------------------------------------
                        //
                        // alternation
                        //
                        //------------------------------------------------------
                    case ALT: {
                        AutoPtr<Logic>   res = new Or();
                        if( motif->size <= 0 ) throw Specific::Exception(CallSign,"empty left sub-expression in '%s'", expr);
                        {
                            AutoPtr<Logic> alt = new Or();
                            *alt <<  motif.yield(); // lhs: current motif
                            *alt <<  subExpr();     // rhs: next expression
                            return alt.yield();
                        }
                    } break;

                        //------------------------------------------------------
                        //
                        // escape sequence
                        //
                        //------------------------------------------------------
                    case BACKSLASH:
                        escExpr(*motif);
                        break;

                        //------------------------------------------------------
                        //
                        // simple joker
                        //
                        //------------------------------------------------------
                    case '?':
                    case '+':
                    case '*':
                        simpleJoker(*motif,C);
                        break;

                        //------------------------------------------------------
                        //
                        // sub Banck
                        //
                        //------------------------------------------------------
                        



                        //------------------------------------------------------
                        //
                        // default
                        //
                        //------------------------------------------------------
                    default:
                        *motif << new Byte(C);
                }
            }

        RETURN:
            if(motif->size<=0)
                throw Specific::Exception(CallSign,"empty sub-expression in '%s'", expr);

            return motif.yield();
        }

    }

}
