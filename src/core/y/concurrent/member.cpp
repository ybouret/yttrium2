
#include "y/concurrent/member.hpp"
#include "y/format/decimal.hpp"

#include <cassert>
#include <iostream>
#include <cstring>

namespace Yttrium
{
    namespace Concurrent
    {

        Member:: ~Member() noexcept
        {
        }

        Member:: Member(const size_t sz,
                        const size_t rk) noexcept:
        size(sz),
        rank(rk),
        indx(rank+1),
        logo()
        {
            assert(size>0);
            assert(rank<size);
            assert(size<=MaxSize);
            updateLogo();
        }


        void Member:: updateLogo() noexcept
        {
            static const char  dot[] = ".";
            static const char  nul[] = "0";

            char * const       buff = (char *) memset( (void *)logo,0, TagSize );
            const Decimal      sd(size);
            const char * const sds = sd.c_str();
            const size_t       sdl = strlen( sds ); assert(sdl<=(size_t)Digits);
            const Decimal      id(indx);
            const char * const ids = id.c_str();
            const size_t       idl = strlen( ids ); assert(idl<=sdl);

#if defined(_MSC_VER)
#pragma warning ( disable : 4996 )
#endif
            strncat(buff,sds,TagSize-1);
            strncat(buff,dot,TagSize-1);
            for(size_t i=sdl-idl;i>0;--i) strncat(buff,nul,TagSize-1);
            strncat(buff,ids,TagSize-1);

        }

        const char * Member:: c_str() const noexcept
        {
            return logo;
        }

        Member:: Member(const Member &m) noexcept :
        size(m.size),
        rank(m.rank),
        indx(m.indx),
        logo()
        {
            memcpy( (void*)logo, m.logo, sizeof(logo) );
        }


    }

}

