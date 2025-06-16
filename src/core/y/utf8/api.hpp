//! \file

#ifndef Y_UTF8_Included
#define Y_UTF8_Included 1


#include "y/container/readable.hpp"

namespace Yttrium
{

    struct UTF8
    {
        static const char * const CallSign;
        static const uint8_t BulkInfo = 0x80;
        static const uint8_t BulkMask = 0xC0;

        struct CodePoints
        {
            uint32_t head; //!< first valid codepoint
            uint32_t tail; //!< last  valid codepoint
            uint8_t  mask; //!< Byte1 mask to extract info
            uint8_t  info; //!< Byte1 info once masked
            unsigned shift[4];
            uint32_t dword[4];

            uint8_t  data(const unsigned iByte, const uint32_t cp) const noexcept;

        };

        static const unsigned   Count = 4;
        static const CodePoints Table[Count];
        static const uint32_t   MaxCodePoint;

        class Encoding
        {
        public:
            Encoding(const uint32_t);
            ~Encoding() noexcept;
            Encoding(const Encoding &) noexcept;

            friend std::ostream & operator<<(std::ostream &,const Encoding &);

            const size_t  size;
            const uint8_t byte[4];

        private:
            Y_Disable_Assign(Encoding);


        };

        class Decoding
        {
        public:
            Decoding();
            ~Decoding() noexcept;

        private:
            uint32_t cp;
        };

    };

}

#endif

