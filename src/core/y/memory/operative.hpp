
//! \file

#ifndef Y_Memory_Operative_Included
#define Y_Memory_Operative_Included 1

#include "y/core/setup.hpp"

namespace Yttrium
{
    namespace Memory
    {

        class Operative
        {
        public:
            typedef void (*QuitProc)(void *);

            explicit Operative(void * const entry,
                               const size_t count,
                               const size_t width,
                               QuitProc     _quit);

            virtual ~Operative() noexcept;

            uint8_t * const workspace;
            size_t          numBlocks;
            const size_t    blockSize;
            QuitProc const  quit;

        private:
            Y_Disable_Copy_And_Assign(Operative);
            void release_() noexcept;

        };
    }

}

#endif
