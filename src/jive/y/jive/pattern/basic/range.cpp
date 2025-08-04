
#include "y/jive/pattern/basic/range.hpp"
#include "y/stream/output.hpp"
#include "y/ascii/embedding.hpp"

namespace Yttrium
{
    namespace Jive
    {
        Range:: Range(const uint8_t a, const uint8_t b) noexcept :
        Pattern(UUID),
        lower(a), upper(b)
        {
            if(lower>upper) CoerceSwap(lower,upper);
        }

        Range:: Range(const Range &_) noexcept : Pattern(_), lower(_.lower), upper(_.upper)
        {
            assert(lower<=upper);
        }

        OutputStream & Range:: viz(OutputStream &fp) const
        {
            nodeName(fp) << '[';
            {
                String label = ASCII::Embedding::Char[lower];
                label       += '-';
                label       += ASCII::Embedding::Char[upper];
                Label(fp, label);
            }
            fp << ",shape=box";
            return Endl(fp << ']');
        }

        size_t Range:: serialize(OutputStream &fp) const
        {
            size_t res = fp.emitCBR(uuid);
            fp.write(lower);
            fp.write(upper);
            return res+2;
        }

        bool Range:: accepts(Token &token, Source &source) const
        {
            assert(0==token.size);
            Char *ch = source.query();
            if(!ch)
                return false;

            const uint8_t c = **ch;
            if(c<lower||c>upper) {
                source.store(ch);
                return false;
            }

            token.pushTail(ch);
            return true;
        }

        FirstChars Range:: firstChars() const noexcept
        {
            FirstChars fc;
            fc.add(lower,upper);
            return fc;
        }

    }
}
