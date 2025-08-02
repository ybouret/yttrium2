
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

        void Source:: store(Token &token) noexcept
        {
            buffer.mergeHead(token);
        }

        void Source:: stash(const Token &token)
        {
            Token tmp(token);
            buffer.mergeHead(tmp);
        }

        size_t Source:: cached() const noexcept { return buffer.size; }

        void   Source:: skip(size_t n) noexcept
        {
            assert(n>=buffer.size);
            static Char::Cache &pool = Char::CacheLocation();
            while(n-- > 0)
                pool.banish( buffer.popHead() );
        }


    }

}

