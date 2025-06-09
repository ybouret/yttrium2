//! \file

#ifndef Y_Stream_IO_Codec64_Included
#define Y_Stream_IO_Codec64_Included 1

#include "y/calculus/integer-log2.hpp"
#include "y/core/setup.hpp"

namespace Yttrium
{

    namespace IO
    {
        class Codec64
        {
        public:
            static const unsigned MaxInputBytes = sizeof(uint64_t);
            static const unsigned MaxInputBits  = 8 * MaxInputBytes;
            static const unsigned HeaderBits    = IntegerLog2<MaxInputBits>::Value;
            Codec64(const uint64_t qw) noexcept;
            ~Codec64() noexcept;

        private:
            Y_Disable_Assign(Codec64);
        };
    };

}

#endif

