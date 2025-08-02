
#include "y/jive/token.hpp"
#include "y/ability/lockable.hpp"

namespace Yttrium
{
    namespace Jive
    {
        Token:: Token() : Char::List(), Recyclable(), pool( Char::CacheInstance() )
        {
        }


        void Token:: clear() noexcept
        {
            while(size>0) pool.banish(popTail());
        }

        Token:: ~Token() noexcept
        {
            clear();
        }



        Token:: Token(const Token &other) : Char::List(), Recyclable(), pool( other.pool )
        {
            try {
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

    }
}
