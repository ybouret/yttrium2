
#include "y/jive/pattern/joker.hpp"


namespace Yttrium
{
    namespace Jive
    {
        Joker:: ~Joker() noexcept
        {

        }

        Joker:: Joker(const uint32_t t, const Motif &m) noexcept :
        Pattern(t),
        motif(m) {}


        Joker:: Joker(const Joker &jk) noexcept :
        Pattern(jk),
        motif(jk.motif)
        {
        }

    }

}

