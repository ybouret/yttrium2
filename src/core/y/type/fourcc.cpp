
#include "y/type/fourcc.hpp"
#include "y/format/hexadecimal.hpp"
#include <cstring>
#include <cctype>
#include <cstdio>

namespace Yttrium
{
    FourCC:: ~FourCC() noexcept { memset(text,0,sizeof(text)); }

    FourCC:: FourCC(const FourCC &fcc) noexcept :
    LegacyString(), text()
    {
        memcpy(text,fcc.text,sizeof(text));
    }


    FourCC:: FourCC(const uint32_t uuid) noexcept :
    text()
    {
        memset(text,0,sizeof(text));
        for(int shift=0;shift<=24;shift+=8)
        {
            const uint8_t b = uint8_t(uuid>>shift);
            const char    c = b;
            if( isgraph(c) )
            {
                char buff[4];
                memset(buff,0,sizeof(buff));
                snprintf(buff,sizeof(buff), "%c", c);
                strcat(text,buff);
            }
            else
            {
                strcat(text,Hexadecimal::LowerByte[b]);
            }
        }
    }

    const char * FourCC:: c_str() const noexcept { return text; }


#if 0
    static bool isAuthorized(const char c) noexcept
    {
        static const char extra[] = "-_:";
        return 0 != strchr(extra,c);
    }
#endif

#if 0
    const char * FourCC:: ToText(const uint32_t uuid) noexcept
    {
        static char data[128];
        memset(data,0,sizeof(data));

        for(int shift=0;shift<=24;shift+=8)
        {
            const uint8_t b = uint8_t(uuid>>shift);
            const char    c = b;
            if( isgraph(c) )
            {
                char buff[8];
                memset(buff,0,sizeof(buff));
                snprintf(buff,sizeof(buff), "%c", c);
                strcat(data,buff);
            }
            else
            {
                strcat(data,Hexadecimal::Text[b]);
            }
        }


        return data;
    }
#endif
    

}

