
#include "y/jive/pattern.hpp"


namespace Yttrium
{
    namespace Jive
    {
        Pattern:: Pattern(const uint32_t t) noexcept :
        uuid(t),
        next(0),
        prev(0),
        self(0)
        {
        }

        Pattern:: ~Pattern() noexcept
        {
        }

        Pattern:: Pattern(const Pattern &p) noexcept :
        CountedObject(),
        Vizible(),
        Serializable(),
        uuid(p.uuid),
        next(0),
        prev(0),
        self(0)
        {

        }

        bool Pattern:: feeble() const { return !strong(); }

        bool Pattern:: flexible() const { return !univocal(); }

    }

}

#include "y/exception.hpp"
#include <cstdio>

namespace Yttrium
{
    namespace Jive
    {
        String Pattern:: ToRegExp(const String &str)
        {
            const size_t n = str.size();
            if(n<=0) throw Specific::Exception("Pattern::ToRegExp","empty source string");
            String res;
            {
                char         data[8] = { '\\', 'x', 0, 0, 0, 0, 0, 0 };
                char * const buff = data+2;
                for(size_t i=1;i<=n;++i)
                {
                    const char     c = str[i];
                    const unsigned x = (uint8_t)c;
                    snprintf(buff,3, "%02x", x);
                    res += data;
                }
            }
            return res;
        }
    }

}
