//! \file

#ifndef Y_Memory_Dead_Pool_Included
#define Y_Memory_Dead_Pool_Included 1

#include "y/memory/object/guild.hpp"

namespace Yttrium
{
    namespace Memory
    {

        class DeadPool
        {
        public:
            static const unsigned WordsForPool = 4;
            explicit DeadPool(const size_t blockSize);
            virtual ~DeadPool() noexcept;
            

        private:
            Y_Disable_Copy_And_Assign(DeadPool);
            Memory::Object::Guild guild;
            void * const          entry;
            void *                words[WordsForPool];
        };
    }
}

#endif

