
#include "y/format/justify.hpp"
#include "y/string/length.hpp"
#include "y/check/usual.hpp"

namespace Yttrium
{

    Justify:: ~Justify() noexcept
    {
        
    }

    Justify:: Justify(const Justify &_) noexcept :
    text(_.text),
    size(_.size),
    type(_.type),
    width(_.width)
    {
    }

    Justify:: Justify(const String &s, const size_t w, const Type t) noexcept :
    text(s.c_str()),
    size(s.size()),
    type(t),
    width(w)
    {
    }

    Justify:: Justify(const char * const s, const size_t w, const Type t) noexcept :
    text(s),
    size(StringLength(s)),
    type(t),
    width(w)
    {
    }

    std::ostream & Justify:: raw(std::ostream &os) const
    {
        assert( Good(text,size) );
        for(size_t i=0;i<size;++i) os << text[i];
        return os;
    }

    static inline std::ostream & jskp(std::ostream &os, size_t n)
    {
        while(n-- > 0) os << ' ';
        return os;
    }


    std::ostream & operator<<(std::ostream &os, const Justify &J)
    {
        if(J.size>=J.width) return J.raw(os);
        const size_t space = J.width - J.size;
        switch(J.type)
        {
            case Justify::Left:  return jskp( J.raw(os), space);
            case Justify::Right: return J.raw( jskp(os,space) );
            case Justify::Center: {
                const size_t nl = space >> 1;
                const size_t nr = space-nl;
                return jskp( J.raw( jskp(os,nl) ), nr );
            }
        }
        return os;
    }

}
