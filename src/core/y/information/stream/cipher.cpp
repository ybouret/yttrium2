
#include "y/information/stream/cipher.hpp"
#include "y/check/usual.hpp"

namespace Yttrium
{
    namespace Information
    {
        StreamCipher:: ~StreamCipher() noexcept
        {
        }

        StreamCipher::  StreamCipher() noexcept : Serializable()
        {
        }


        void StreamCipher:: transform(void * const target, const void * const source, size_t length) noexcept
        {
            assert( Good(target,length) );
            assert( Good(source,length) );
            uint8_t *       tgt = static_cast<uint8_t *>(target);
            const uint8_t * src = static_cast<const uint8_t *>(source);

            StreamCipher &self = *this;
            while(length-- > 0)
            {
                *(tgt++) = self( *(src++) );
            }

        }

    }
}
