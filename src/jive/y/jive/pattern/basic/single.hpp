
//! \file

#ifndef Y_Pattern_Single_Included
#define Y_Pattern_Single_Included 1

#include "y/jive/pattern.hpp"

namespace Yttrium
{
    namespace Jive
    {

        Y_Jive_Pattern_Decl(Single,'S','N','G','L');

        explicit Single(const uint8_t) noexcept;
        Single(const Single &)         noexcept;

        virtual bool       accepts(Token &,Source &) const;
        virtual void       viz(OutputStream&)        const;
        virtual FirstChars firstChars()     const noexcept;
        virtual size_t     serialize(OutputStream &) const;
        
        const uint8_t code;

        Y_Jive_Pattern_End(Single);
    }
}

#endif

