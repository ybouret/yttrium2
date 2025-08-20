
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


        Char * Source:: get()
        {
            return buffer.size ? buffer.popHead() : handle->query();
        }

        void Source:: put(Char *const ch) noexcept
        {
            assert(0!=ch);
            buffer.pushHead(ch);
        }

        void Source:: put(Token &token) noexcept
        {
            buffer.mergeHead(token);
        }

        void Source:: dup(const Token &token)
        {
            Token tmp(token);
            buffer.mergeHead(tmp);
        }

        size_t Source:: cache() const noexcept { return buffer.size; }

        void   Source:: sweep(size_t n) noexcept
        {
            assert(n<=buffer.size);
            static Char::Cache &pool = Char::CacheLocation();
            while(n-- > 0)
                pool.banish( buffer.popHead() );
        }

        bool Source:: ready()
        {
            if(buffer.size)                            return true;
            Char * const ch = handle->query(); if(!ch) return false;
            (void) buffer.pushTail(ch);        return         true;
        }

        const Char * Source:: peek()
        {
            if( ready() )
            {
                assert(buffer.size>0);
                return buffer.head;
            }
            else
            {
                return 0;
            }
        }

        void Source:: fetch(size_t n)
        {
            while(n-- > 0)
            {
                if(Char * const ch = handle->query()) { buffer.pushTail(ch); continue; }
                break;
            }
        }

        const Context & Source:: context() const noexcept
        {
            return *handle;
        }

        bool Source:: query(char &c)
        {
            Char * const ch = get();
            if(!ch) return false;
            c = (char) **ch;
            static Char::Cache &pool = Char::CacheLocation();
            pool.banish(ch);
            return true;
        }


        void Source:: store(const char)
        {
            throw Specific::Exception("Jive::Source","no possible binary store()");
        }
    }

}

