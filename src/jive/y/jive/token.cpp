
#include "y/jive/token.hpp"
#include "y/ability/lockable.hpp"
#include "y/ascii/printable.hpp"

namespace Yttrium
{
    namespace Jive
    {
        Token:: Token() noexcept : Char::List(), Recyclable()
        {
        }


        void Token:: clear() noexcept
        {
            while(size>0)
            {
                static Char::Cache & pool = Char::CacheLocation();
                pool.banish(popTail());
            }
        }

        Token:: ~Token() noexcept
        {
            clear();
        }



        Token:: Token(const Token &other) : Char::List(), Recyclable()
        {
            try {
                static Char::Cache & pool = Char:: CacheInstance();
                for(const Char *ch=other.head;ch;ch=ch->next)
                {
                    pushTail( pool.mirror(ch) );
                }
            }
            catch(...)
            {
                clear(); throw;
            }
        }


        void Token:: free() noexcept { clear();  }

        Token & Token:: skip() noexcept
        {
            if(size>0)
            {
                static Char::Cache & pool = Char:: CacheLocation();
                pool.banish( popHead() );
            }
            return *this;
        }

        Token & Token:: trim() noexcept
        {
            if(size>0)
            {
                static Char::Cache & pool = Char:: CacheLocation();
                pool.banish( popTail() );
            }
            return *this;
        }



        std::ostream & operator<<(std::ostream &os, const Token &token)
        {
            for(const Char *ch=token.head;ch;ch=ch->next)
            {
                os << ASCII::Printable::Char[ **ch ];
            }
            return os;
        }

        String Token:: toString(const size_t nskip, const size_t ntrim) const
        {
            const size_t rem = nskip+ntrim;
            if(rem>=size) return String();
            const Char *curr = head; for(size_t i=nskip;i>0;--i) curr=curr->next;
            String      res;
            for(size_t i=size-rem;i>0;--i,curr=curr->next)
                res += char(**curr);
            return res;

        }


    }
}
