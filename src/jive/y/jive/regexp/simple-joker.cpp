
#include "y/jive/regexp/compiler.hpp"
#include "y/jive/pattern/all.hpp"
#include "y/pointer/auto.hpp"
#include "y/exception.hpp"
#include "y/ascii/printable.hpp"

namespace Yttrium
{
    namespace Jive
    {

        void RegExp::Compiler:: simpleJoker(Logic &p, const char jk)
        {
            if(p.size<=0) throw Specific::Exception(CallSign,"no expression before '%s' in '%s'", ASCII::Printable::Text(jk), expr);

            const Motif q = p.popTail();
            switch(jk)
            {
                case '?' : p << new Option(q);   break;
                case '*' : p << new Repeat(q,0); break;
                case '+' : p << new Repeat(q,1); break;
                default:
                    throw Specific::Exception(CallSign,"unexpected joker '%s'", ASCII::Printable::Text(jk));
            }
        }
    }

}


