
#include "y/jive/token.hpp"
#include "y/ability/lockable.hpp"
#include "y/ascii/printable.hpp"
#include "y/stream/output.hpp"

namespace Yttrium
{
    namespace Jive
    {
        Token:: Token() noexcept : Char::List(), Recyclable(), Serializable()
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



        Token:: Token(const Token &other) : Char::List(), Recyclable(), Serializable()
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

        size_t Token:: serialize(OutputStream &fp) const
        {
            size_t res = fp.emitVBR(size);
            for(const Char *ch=head;ch;ch=ch->next,++res)
                fp.write( (char) **ch );
            return res;
        }

        bool operator==(const Token &lhs, const Token &rhs) noexcept
        {
            const size_t n = lhs.size; if(n!=rhs.size) return false;

            for(const Char * l = lhs.head, *r = rhs.head; l; l=l->next, r=r->next)
            {
                assert(l);
                assert(r);
                if( **l != **r) return false;
            }

            return true;
        }

        apn Token:: toNatural() const
        {
            const apn ten(10);
            const uint8_t zero = '0';
            const uint8_t nine = '9';
            apn res = 0;
            for(const Char *ch=head;ch;ch=ch->next)
            {
                const uint8_t d = **ch;
                if(d<zero||d>nine) throw Exception("invalid digit in Token::toNatural");
                res *= 10;
                res += (int)(d-zero);
            }
            return res;
        }



    }
}
