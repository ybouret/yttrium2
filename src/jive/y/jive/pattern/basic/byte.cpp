
#include "y/jive/pattern/basic/byte.hpp"
#include "y/stream/output.hpp"
#include "y/ascii/embedding.hpp"

namespace Yttrium
{
    namespace Jive
    {
        Byte:: Byte(const uint8_t a) noexcept : Pattern(UUID), code(a)   { I_am<Byte>(); }
        Byte:: Byte(const Byte &_) noexcept : Pattern(_), code(_.code) { I_am<Byte>(); }

        OutputStream & Byte:: viz(OutputStream &fp) const
        {
            nodeName(fp) << '[';
            Label(fp, ASCII::Embedding::Char[code] );
            fp << ",shape=square";
            return Endl(fp << ']');
        }

        size_t Byte:: serialize(OutputStream &fp) const
        {
            size_t res = fp.emitCBR(uuid);
            fp.write( (char)code);
            return res+1;
        }

        bool Byte:: accepts(Token &token, Source &source) const
        {
            assert(0==token.size);
            Char *ch = source.get();
            if(!ch)
                return false;

            if(code != **ch) {
                source.put(ch);
                return false;
            }

            token.pushTail(ch);
            return true;
        }

        FirstChars Byte:: firstChars() const noexcept
        {
            FirstChars fc;
            fc.add(code);
            return fc;
        }

        bool Byte:: strong() const { return true; }

        bool Byte:: univocal() const { return true; }

    }
}
