//! \file

#ifndef Y_UTF8_Included
#define Y_UTF8_Included 1


#include "y/core/setup.hpp"

namespace Yttrium
{

    struct UTF8
    {
        static const char * const CallSign;
        static const uint8_t BulkInfo = 0x80;
        static const uint8_t BulkMask = 0xC0;

        struct CodePoint
        {
            uint32_t head; //!< first valid codepoint
            uint32_t tail; //!< last  valid codepoint
            uint8_t  mask; //!< Byte1 mask to extract info
            uint8_t  info; //!< Byte1 info once masked
        };

        static const CodePoint CodePoints[4];
        static const uint32_t  MaxCodePoint;
        
        class Encoding
        {
        public:
            Encoding(const uint32_t cp);
            ~Encoding() noexcept;

            const size_t  size;
            const uint8_t byte[4];

        private:
            Y_Disable_Assign(Encoding);


        };


    };

}

#endif

