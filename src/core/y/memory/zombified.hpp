
//! \file

#ifndef Y_Memory_Zombified_Included
#define Y_Memory_Zombified_Included 1

#include "y/memory/object/guild.hpp"
#include <cassert>

namespace Yttrium
{
    namespace Memory
    {

        template <typename T>
        class Zombified
        {
        public:
            inline explicit Zombified() : provider(sizeof(T)) {}
            inline virtual ~Zombified() noexcept {}

            inline T *  summon()
            {
                return static_cast<T *>(provider.acquireBlock());
            }

            inline void banish( T * const zombi ) noexcept
            {
                assert(0!=zombi);
                provider.releaseBlock(zombi);
            }

        private:
            Y_Disable_Copy_And_Assign(Zombified);
            Object::Guild provider;
        };
    }

}

#endif
