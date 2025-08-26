

#include "y/jive/regexp/compiler.hpp"
#include "y/jive/pattern/all.hpp"
#include "y/pointer/auto.hpp"
#include "y/system/exception.hpp"
#include "y/ascii/printable.hpp"

namespace Yttrium
{
    namespace Jive
    {
        Pattern * RegExp:: Compiler:: escBank()
        {
            //std::cerr << "escExpr" << std::endl;

            assert( BACKSLASH == curr[-1] );

            if(curr>=last) throw Specific::Exception(CallSign,"unfinished escape sequence in '%s'",expr);

            const char c = *(curr++);

            switch(c)
            {
                    // direct
                case LBRACK:
                case RBRACK:
                case CARET:
                case '-':
                case BACKSLASH:
                case LPAREN:
                case RPAREN:
                    return new Byte( (uint8_t)c );

                    // control
#include "esc-ctrl.hxx"

                    // bad...
                default:
                    break;
            }

            throw Specific::Exception(CallSign,"unknown escaped sequence '\\%s' in '%s'", ASCII::Printable::Text(c), expr);
        }
    }

}


