
#include "y/jive/regexp/compiler.hpp"
#include "y/jive/pattern/all.hpp"
#include "y/pointer/auto.hpp"
#include "y/system/exception.hpp"
#include "y/jive/pattern/posix.hpp"

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
                        *motif << escExpr();
                        break;

                        //------------------------------------------------------
                        //
                        // dot
                        //
                        //------------------------------------------------------
                    case '.':
                        motif->pushTail( posix::dot() );
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
                        // ignore case
                        //
                        //------------------------------------------------------
                    case AMPERSAND:
                        if( motif->size <= 0 ) throw Specific::Exception(CallSign,"empty sub-expression before '%c' in '%s'", C, expr);
                        *motif <<  Pattern::Insensitive( motif->popTail() );
                        break;

                        //------------------------------------------------------
                        //
                        // sub Bank
                        //
                        //------------------------------------------------------
                    case LBRACK:
                        *motif << subBank();
                        break;

                    case RBRACK:
                        throw Specific::Exception(CallSign,"'%c' must be escaped in '%s''", RBRACK, expr);


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
