
#include "y/jive/token.hpp"
#include "y/ability/lockable.hpp"

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

    }
}
