
//! \file

#ifndef Y_Jive_FirstChars_Included
#define Y_Jive_FirstChars_Included 1

#include "y/core/setup.hpp"
#include "y/ostream-proto.hpp"

namespace Yttrium
{
    namespace Jive
    {

        class FirstChars
        {
        public:
            static const unsigned Count = 256;
            static const unsigned Bytes = Count/8;
            typedef void (*Proc)(const uint8_t, const uint8_t, void *);

            FirstChars() noexcept;
            FirstChars(const FirstChars &) noexcept;
            FirstChars & operator=(const FirstChars &) noexcept;
            Y_OSTREAM_PROTO(FirstChars);

            void free() noexcept;
            void all()  noexcept;
            void add(const uint8_t)    noexcept;
            void add(uint8_t, uint8_t) noexcept;
            void sub(const uint8_t)    noexcept;
            void sub(uint8_t, uint8_t) noexcept;

            FirstChars & operator +=(const FirstChars &) noexcept;
            FirstChars & operator -=(const FirstChars &) noexcept;

            void run(Proc proc, void * const args) const;

            const size_t size;
        private:
            uint8_t data[Bytes];
            bool getbit(const uint8_t b) const noexcept;
            void setbit(const uint8_t b) noexcept;
            void clrbit(const uint8_t b) noexcept;

            unsigned findLowerBit(const unsigned) const noexcept;
            unsigned findUpperBit(const unsigned) const noexcept;
            static void Print(const uint8_t, const uint8_t, void *);
        };
    }
}

#endif

