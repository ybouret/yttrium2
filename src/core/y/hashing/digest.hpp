//! \file

#ifndef Y_Hashing_Digest_Included
#define Y_Hashing_Digest_Included 1

#include "y/container/contiguous.hpp"
#include "y/memory/buffer/rw.hpp"

namespace Yttrium
{
    namespace Hashing
    {

        class Digest :
        public Contiguous< Writable<uint8_t> >,
        public Memory::ReadWriteBuffer
        {
        public:
            explicit Digest(const size_t width);
            virtual ~Digest() noexcept;


        private:
            class Code;
            Y_Disable_Assign(Digest);
            Code * const code;
        };

    }
}

#endif

