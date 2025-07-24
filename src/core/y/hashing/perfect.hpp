//! \file

#ifndef Y_Hashing_Perfect_Included
#define Y_Hashing_Perfect_Included 1

#include "y/memory/buffer/ro.hpp"

namespace Yttrium
{
    namespace Hashing
    {

        class Perfect
        {
        public:
            static const char * const CallSign; //!< "Hashing::Perfect"

            explicit Perfect();
            virtual ~Perfect() noexcept;

            void operator()(const void *path, const size_t size, const int key);
            void operator()(const char * const, const int);
            void operator()(const Memory::ReadOnlyBuffer &, const int);

        private:
            class Code;
            Y_Disable_Copy_And_Assign(Perfect);
            Code * const code;
        };
    }
}

#endif

