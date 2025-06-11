//! \file

#ifndef Y_Memory_Zombies_Included
#define Y_Memory_Zombies_Included

#include "y/memory/page.hpp"
#include "y/ability/caching.hpp"

namespace Yttrium
{
    namespace Memory
    {

        //! pool of zombies of same block size
        class Zombies : public Caching
        {
        public:
            class Code;
            explicit Zombies(const size_t userBlockSize);
            virtual ~Zombies() noexcept;
            
            virtual void   gc(uint8_t) noexcept;
            virtual size_t count() const noexcept;
            virtual void   cache(const size_t);

        private:
            Y_Disable_Copy_And_Assign(Zombies);
            Code * const code;
        };

    }
}

#endif

