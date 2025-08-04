

#include "y/jive/pattern/joker/repeat.hpp"
#include "y/stream/output.hpp"
#include "y/string/format.hpp"
#include "y/format/decimal.hpp"

namespace Yttrium
{
    namespace Jive
    {

        Repeat:: Repeat(const Motif &m, const size_t n) :
        Joker(UUID,m),
        minCount(n)
        {
            I_am<Repeat>();
        }

        Repeat:: Repeat(const Repeat &rep) noexcept :
        Joker(rep),
        minCount(rep.minCount)
        {
            I_am<Repeat>();
        }


        size_t Repeat:: serialize(OutputStream &fp) const
        {
            size_t res = fp.emitCBR(uuid);
            res += fp.emitVBR(minCount);
            return res + motif->serialize(fp);
        }

        bool Repeat:: accepts(Token &token, Source &source) const
        {
            assert(0==token.size);
            size_t count = 0;
            while(true)
            {
                Token tmp;
                if(motif->accepts(tmp,source))
                {
                    ++count;
                    token.mergeTail(tmp);
                    continue;
                }
                break;
            }
            if(count>=minCount) return true;

            source.store(token);
            return false;
        }


        bool Repeat:: strong() const
        {
            return minCount >0;
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

        bool Repeat:: univocal() const {
            return false;
        }


    }

}
