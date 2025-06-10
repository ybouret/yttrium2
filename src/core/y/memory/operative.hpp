
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
            typedef void (*InitProc)(void       * const target,
                                     const void * const source,
                                     const size_t       indexx);

            typedef void (*QuitProc)(void * const target);

            explicit Operative(void * const       entry,
                               const size_t       count,
                               const size_t       width,
                               InitProc const     _init,
                               const void * const _args,
                               QuitProc const     _quit);

            virtual ~Operative() noexcept;

        protected:
            uint8_t * const workspace;
            size_t          numBlocks;
            
        public:
            const size_t    blockSize;

        private:
            Y_Disable_Copy_And_Assign(Operative);
            QuitProc const  quit;
            void release_() noexcept;

        };
    }

}

#endif
