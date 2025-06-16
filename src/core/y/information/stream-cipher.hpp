//! \file

#ifndef Y_Information_Stream_Cipher_Included
#define Y_Information_Stream_Cipher_Included 1

#include "y/ability/serializable.hpp"

namespace Yttrium
{
    namespace Information
    {
        class StreamCipher : public Serializable
        {
        public:
            explicit StreamCipher() noexcept;
            virtual ~StreamCipher() noexcept;

            virtual uint8_t operator()(const uint8_t) noexcept = 0;
            
        private:
            Y_Disable_Copy_And_Assign(StreamCipher);
        };
    }
}

#endif

