


#include "y/jive/pattern/joker/amount.hpp"
#include "y/stream/output.hpp"
#include "y/string/format.hpp"
#include "y/format/decimal.hpp"
#include "y/system/exception.hpp"

namespace Yttrium
{
    namespace Jive
    {

        Amount:: Amount(const Motif &m, const size_t nmin, const size_t nmax) :
        Joker(UUID,m),
        minCount(nmin),
        maxCount(nmax)
        {
        }

        Amount:: Amount(const Amount &rep) noexcept :
        Joker(rep),
        minCount(rep.minCount),
        maxCount(rep.maxCount)
        {
        }


        size_t Amount:: serialize(OutputStream &fp) const
        {
            size_t res = fp.emitCBR(uuid);
            res += fp.emitVBR(minCount);
            res += fp.emitVBR(maxCount);
            return res + motif->serialize(fp);
        }

        bool Amount:: accepts(Token &token, Source &source) const
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
            if(count>=minCount && count<=maxCount) return true;

            source.store(token);
            return false;
        }


        bool Amount:: strong() const
        {
            return minCount >0;
        }

        OutputStream & Amount:: viz(OutputStream &fp) const
        {
            nodeName(fp) << '[';

            const String label = Formatted::Get(">=%s", Decimal(minCount).c_str());
            Label(fp,label);
            fp << ",shape=ellipse";
            Endl(fp << ']');
            motif->viz(fp);
            return Endl( to( & *motif , fp) );
        }

        FirstChars Amount:: firstChars() const noexcept
        {
            return motif->firstChars();
        }


    }

}
