
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


            typedef void (*InitProc)(void * const target,
                                     void * const source,
                                     const size_t indexx,
                                     void * const params);

            typedef void (*QuitProc)(void * const target);

            explicit Operative(void * const       entry,
                               const size_t       count,
                               const size_t       width,
                               InitProc const     onInit,
                               void * const       source,
                               void * const       params,
                               QuitProc const     onQuit);

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
