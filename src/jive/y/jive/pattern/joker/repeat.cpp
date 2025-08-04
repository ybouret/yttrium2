

#include "y/jive/pattern/joker/repeat.hpp"
#include "y/stream/output.hpp"
#include "y/string/format.hpp"
#include "y/format/decimal.hpp"

namespace Yttrium
{
    namespace Jive
    {

        Repeat:: Repeat(const Motif &m, const size_t n) noexcept :
        Joker(UUID,m),
        minCount(n)
        {
        }

        Repeat:: Repeat(const Repeat &rep) noexcept :
        Joker(rep),
        minCount(rep.minCount)
        {
        }


        size_t Repeat:: serialize(OutputStream &fp) const
        {
            size_t res = fp.emitCBR(uuid);
            res += fp.emitVBR(minCount);
            return res + motif->serialize(fp);
        }

        bool Repeat:: accepts(Token &token, Source &source) const
        {

        }


        bool Repeat:: strong() const
        {
            return minCount >0 && motif->strong();
        }

        OutputStream & Repeat:: viz(OutputStream &fp) const
        {
            nodeName(fp) << '[';
            switch(minCount)
            {
                case '0': Label(fp,'*'); break;
                case '1': Label(fp,'+'); break;
                default: {
                    const String label = Formatted::Get(">=%s", Decimal(minCount).c_str());
                    Label(fp,label); } break;
            }
            fp << ",shape=circle";
            Endl(fp << ']');
            motif->viz(fp);
            return Endl( to( & *motif , fp) );
        }

        FirstChars Repeat:: firstChars() const noexcept
        {
            return motif->firstChars();
        }


    }

}
