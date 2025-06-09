//! \file

#ifndef Y_Stream_IO_Char_Included
#define Y_Stream_IO_Char_Included 1

#include "y/core/setup.hpp"

namespace Yttrium
{

    namespace IO
    {

        class Char
        {
        public:
            class Netherworld;
            static Char * New(const uint8_t code);
            static void   Delete(Char * const) noexcept;

            Char *  next;
            Char *  prev;
            uint8_t code;

        private:
            friend class Netherworld;
            Char(const uint8_t a) noexcept;
            Char(const Char &)    noexcept;
            ~Char() noexcept;
            Y_Disable_Assign(Char);

        };
    }

}

#endif

