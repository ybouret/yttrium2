#include "y/stream/io/char.hpp"
#include "y/memory/io/supply-of.hpp"

namespace Yttrium
{
    namespace IO
    {


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

        typedef Memory::SupplyOf<Char> Manager;

        Char * Char:: New(const uint8_t code)
        {
            static Manager & mgr = Manager::Instance();
            return mgr.summon<uint8_t>(code);
        }

        void Char:: Delete(Char *const ch) noexcept
        {
            assert(0!=ch); assert(Manager::Exists());
            static Manager &mgr = Manager::Location();
            mgr.banish(ch);
        }

        Char * Char:: Copy(const Char * const ch)
        {
            assert(0!=ch); assert(Manager::Exists());
            static Manager &mgr = Manager::Location();
            return mgr.mirror(*ch);
        }

    }
}

