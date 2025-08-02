
#include "y/jive/source.hpp"

namespace Yttrium
{
    namespace Jive
    {
        Source:: ~Source() noexcept
        {
        }

        Source:: Source( Module * const m) noexcept :
        handle(m),
        buffer()
        {
        }

        void Source:: endl() noexcept
        {
            handle->endl();
        }


        Char * Source:: query()
        {
            return buffer.size ? buffer.popHead() : handle->query();
        }

        void Source:: store(Char *const ch) noexcept
        {
            assert(0!=ch);
            buffer.pushHead(ch);
        }



    }

}

