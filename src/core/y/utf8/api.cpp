
#include "y/utf8/api.hpp"
#include "y/system/exception.hpp"
#include "y/hexadecimal.hpp"
#include <cstring>


namespace Yttrium
{

    const char * const UTF8:: CallSign = "UTF-8";

    const UTF8::CodePoint UTF8::CodePoints[] =
    {
        { 0x0000,   0x007F,   0x80, 0x00 },
        { 0x0080,   0x07FF,   0xE0, 0xC0 },
        { 0x0800,   0xFFFF,   0xF0, 0xE0 },
        { 0x010000, 0x10FFFF, 0xF8, 0xF0 }
    };

    const uint32_t UTF8::MaxCodePoint  = CodePoints[3].tail;

    UTF8:: Encoding:: Encoding(const uint32_t cp) :
    size(0),
    byte()
    {
        if(cp>MaxCodePoint) {
            const Hexadecimal hx(cp,Concise);
            const Hexadecimal mx(MaxCodePoint,Concise);
            throw Specific::Exception(CallSign,"codepoint %s exceeds %s", hx.c_str(),mx.c_str());
        }

    }

    UTF8:: Encoding:: ~Encoding() noexcept
    {
        memset( Coerce(byte), 0, sizeof(byte) );
        Coerce(size) = 0;
    }

    

}
