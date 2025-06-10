#include "y/stream/io/char.hpp"
#include "y/concurrent/data/inferno.hpp"

namespace Yttrium
{
    namespace IO
    {
#if 0
        Char:: Pointer:: Pointer(Char * const ch) noexcept :
        pointee(ch)
        {
            assert(0!=ch);
        }

        Char:: Pointer:: ~Pointer() noexcept
        {
            assert(0!=pointee);
            Char::Delete(pointee);
            Coerce(pointee) = 0;
        }

        uint8_t Char::Pointer:: operator*() const noexcept
        {
            assert(0!=pointee);
            return pointee->code;
        }
#endif

        Char:: Char(const Type a) noexcept :
        next(0),
        prev(0),
        code(a)
        {
        }

        Char:: ~Char() noexcept
        {
            
        }

        Char:: Char(const Char &ch) noexcept :
        next(0),
        prev(0),
        code(ch.code)
        {}

        const char * const Char:: CallSign = "IO::Char";

        typedef Concurrent::Inferno<Char> Manager;

        Char * Char:: New(const uint8_t code)
        {
            return Manager::Instance().produce<uint8_t>(code);
        }

        void Char:: Delete(Char *const ch) noexcept
        {
            assert(0!=ch);
            assert(Manager::Exists());
            static Manager &mgr = Manager::Location();
            mgr.zombify(ch);
        }

        Char * Char:: Copy(const Char * const ch)
        {
            assert(0!=ch);
            assert(Manager::Exists());
            static Manager &mgr = Manager::Location();
            return mgr.reenact(*ch);
        }


    }
}

