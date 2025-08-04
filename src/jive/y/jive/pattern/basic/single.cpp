
#include "y/jive/pattern/basic/single.hpp"
#include "y/stream/output.hpp"
#include "y/ascii/embedding.hpp"

namespace Yttrium
{
    namespace Jive
    {
        Single:: Single(const uint8_t a) noexcept : Pattern(UUID), code(a) {}
        Single:: Single(const Single &_) noexcept : Pattern(_), code(_.code) {}

        OutputStream & Single:: viz(OutputStream &fp) const
        {
            nodeName(fp) << '[';
            Label(fp, ASCII::Embedding::Char[code] );
            fp << ",shape=square";
            return Endl(fp << ']');
        }

        size_t Single:: serialize(OutputStream &fp) const
        {
            size_t res = fp.emitCBR(uuid);
            fp.write(code);
            return res+1;
        }

        bool Single:: accepts(Token &token, Source &source) const
        {
            assert(0==token.size);
            Char *ch = source.query();
            if(!ch)
                return false;

            if(code != **ch) {
                source.store(ch);
                return false;
            }

            token.pushTail(ch);
            return true;
        }

        FirstChars Single:: firstChars() const noexcept
        {
            FirstChars fc;
            fc.add(code);
            return fc;
        }

    }
}
