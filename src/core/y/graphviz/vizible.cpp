
#include "y/graphviz/vizible.hpp"
#include "y/format/hexadecimal.hpp"

namespace Yttrium
{
    Vizible:: Vizible() noexcept {}

    Vizible:: ~Vizible() noexcept
    {
    }


    OutputStream & Vizible:: Endl(OutputStream &fp)
    {
        return fp << ';' << '\n';
    }


    OutputStream & Vizible:: name(OutputStream &fp) const
    {
        union {
            uint64_t       data;
            const void *   addr;
        } alias = { 0 };
        alias.addr = this;

        const Hexadecimal id(alias.data,Concise);
        return fp << 'n' << id.c_str();
    }


    OutputStream & Vizible:: to(const Vizible * const target, OutputStream &fp) const
    {
        assert(0!=target);
        return target->name( name(fp) << " -> " );
    }



}

