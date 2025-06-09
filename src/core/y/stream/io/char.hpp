//! \file

#ifndef Y_Stream_IO_Char_Included
#define Y_Stream_IO_Char_Included 1

#include "y/core/setup.hpp"
#include "y/concurrent/life-time.hpp"

namespace Yttrium
{
    namespace Memory
    {
        template <typename> class Inferno;
    }
    namespace IO
    {

        class Char
        {
        public:
            static const System::AtExit::Longevity LifeTime = 1000;
            static const char * const              CallSign;
            
            static Char * New(const uint8_t code);
            static void   Delete(Char * const) noexcept;
            static Char * Copy(const Char * const);

            Char *  next;
            Char *  prev;
            uint8_t code;

        private:
            friend class Memory::Inferno<Char>;
            Char(const uint8_t a) noexcept;
            Char(const Char &)    noexcept;
            ~Char() noexcept;
            Y_Disable_Assign(Char);

        };
    }

}

#endif

