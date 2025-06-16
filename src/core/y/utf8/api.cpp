
#include "y/utf8/api.hpp"
#include "y/system/exception.hpp"
#include "y/hexadecimal.hpp"
#include <cstring>


namespace Yttrium
{

    const char * const UTF8:: CallSign = "UTF-8";

    const UTF8::CodePoints UTF8::Table[Count] =
    {
        { 0x0000,   0x007F,   0x80, 0x00, { 0, 0, 0, 0 }, { 0xff, 0,    0, 0 } },
        { 0x0080,   0x07FF,   0xE0, 0xC0, { 6, 0, 0, 0 }, { 0x1f, 0x3f, 0, 0 } },
        { 0x0800,   0xFFFF,   0xF0, 0xE0, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, },
        { 0x010000, 0x10FFFF, 0xF8, 0xF0, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, }
    };

    uint8_t  UTF8::CodePoints:: data(const unsigned j, const uint32_t cp) const noexcept
    {
        return uint8_t( (cp>>shift[j]) | dword[j] );
    }

    std::ostream & operator<<(std::ostream &os, const UTF8::Encoding &self)
    {
        return Hexadecimal::Display(os,self.byte,self.size);
    }

    const uint32_t UTF8::MaxCodePoint  = Table[Count-1].tail;

    UTF8:: Encoding:: Encoding(const uint32_t cp) :
    size(0),
    byte()
    {
        std::cerr << "cp=" << Hexadecimal(cp) << std::endl;
        for(unsigned i=0;i<Count;++i)
        {
            const CodePoints &code = Table[i];
            if(cp>code.tail)
                continue;

            // first byte
            Coerce(byte[0]) = uint8_t( code.info | code.data(0,cp) );

            // bulk bytes
            for(unsigned j=1;j<=i;++j)
                Coerce(byte[j]) = uint8_t( BulkInfo | code.data(j,cp) );

            Coerce(size) = ++i;
            return;
        }

        assert(cp>MaxCodePoint);
        {
            const Hexadecimal hx(cp,Concise);
            const Hexadecimal mx(MaxCodePoint,Concise);
            throw Specific::Exception(CallSign,"codepoint %s exceeds %s", hx.c_str(),mx.c_str());
        }
    }

    UTF8:: Encoding:: Encoding(const Encoding &other) noexcept :
    size(other.size),
    byte()
    {
        memcpy( Coerce(byte), other.byte, sizeof(byte) );
    }

    UTF8:: Encoding:: ~Encoding() noexcept
    {
        memset( Coerce(byte), 0, sizeof(byte) );
        Coerce(size) = 0;
    }

    

}
