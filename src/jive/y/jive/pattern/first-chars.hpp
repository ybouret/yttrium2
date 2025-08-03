
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


            FirstChars() noexcept;
            FirstChars(const FirstChars &) noexcept;
            FirstChars & operator=(const FirstChars &) noexcept;
            Y_OSTREAM_PROTO(FirstChars);

            void free() noexcept;
            void all()  noexcept;



            const size_t size;
        private:
            uint8_t data[Bytes];
            bool getbit(const uint8_t b) const noexcept;
            void setbit(const uint8_t b) noexcept;
            void clrbit(const uint8_t b) noexcept;
        };
    }
}

#endif

