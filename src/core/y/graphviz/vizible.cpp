
#include "y/graphviz/vizible.hpp"
#include "y/format/hexadecimal.hpp"
#include "y/string.hpp"
#include "y/stream/output.hpp"

namespace Yttrium
{

    const char * Vizible:: Char[256] =
    {
#include "vizible.hxx"
    };

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

    OutputStream & Vizible:: Label(OutputStream &fp, const String &id)
    {
        fp << "label=\"";
        for(size_t i=1;i<=id.size();++i)
        {
            fp << Char[ uint8_t(id[i]) ];
        }
        return fp << "\"";
    }

    OutputStream & Vizible:: Label(OutputStream &fp, const char * const id)
    {
        const String _(id);
        return Label(fp,_);

    }

    OutputStream & Vizible:: Label(OutputStream &fp, const char c)
    {
        const String _(c);
        return Label(fp,_);
    }



}

