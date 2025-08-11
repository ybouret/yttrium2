
#include "y/jive/regexp/compiler.hpp"
#include "y/jive/pattern/all.hpp"
#include "y/pointer/auto.hpp"
#include "y/system/exception.hpp"
#include "y/ascii/printable.hpp"
#include "y/format/hexadecimal.hpp"

namespace Yttrium
{
    namespace Jive
    {
        Pattern * RegExp:: Compiler:: escHexa()
        {
            assert('x'  == curr[-1] );
            assert('\\' == curr[-2] );

            if(curr>=last) throw Specific::Exception(CallSign,"missing first hexa esc char in '%s'", expr);
            const char hiChar = *(curr++);
            const int  hiByte = Hexadecimal::ToDec(hiChar);
            if(hiByte<0) throw Specific::Exception(CallSign,"invalid first hexa esc char '%s' in '%s'", ASCII::Printable::Text(hiChar), expr);

            if(curr>=last) throw Specific::Exception(CallSign,"missing second hexa esc char in '%s'", expr);
            const char loChar = *(curr++);
            const int  loByte = Hexadecimal::ToDec(loChar);
            if(loByte<0) throw Specific::Exception(CallSign,"invalid second hexa esc char '%s' in '%s'", ASCII::Printable::Text(loChar), expr);

            const uint8_t code = uint8_t( (hiByte<<4) | loByte );
            return new Byte( code );
        }

    }

}

