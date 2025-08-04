
#include "y/jive/pattern/joker.hpp"
#include "y/system/exception.hpp"

namespace Yttrium
{
    namespace Jive
    {
        Joker:: ~Joker() noexcept
        {

        }

        Joker:: Joker(const uint32_t t, const Motif &m)   :
        Pattern(t),
        motif(m)
        {
            if(m->feeble())
            {
                const FourCC fcc(uuid);
                throw Specific::Exception(fcc.c_str(),"forbidden feebl '%s' motif", FourCC(motif->uuid).c_str());
            }
        }


        Joker:: Joker(const Joker &jk) noexcept :
        Pattern(jk),
        motif(jk.motif)
        {
        }

    }

}

