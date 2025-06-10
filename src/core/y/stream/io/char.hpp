//! \file

#ifndef Y_Stream_IO_Char_Included
#define Y_Stream_IO_Char_Included 1

#include "y/core/setup.hpp"
#include "y/concurrent/life-time.hpp"

namespace Yttrium
{
    namespace Concurrent
    {
        template <typename> class Inferno;
    }
    namespace IO
    {

        class Char
        {
        public:
            typedef uint8_t Type;

            static const System::AtExit::Longevity LifeTime = LifeTimeOf::IOChars;
            static const char * const              CallSign;
            
            static Char * New(const Type code);
            static void   Delete(Char * const) noexcept;
            static Char * Copy(const Char * const);

            const uint8_t & operator*() const noexcept { return code; }


            Char *  next;
            Char *  prev;
            Type    code;

        private:
            friend class Concurrent::Inferno<Char>;
            Char(const uint8_t a) noexcept;
            Char(const Char &)    noexcept;
            ~Char() noexcept;
            Y_Disable_Assign(Char);

        };
    }

}

#endif

