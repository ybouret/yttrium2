

#include "y/jive/pattern/basic/not.hpp"
#include "y/stream/output.hpp"
#include "y/ascii/embedding.hpp"

namespace Yttrium
{
    namespace Jive
    {
        Not:: Not(const uint8_t a) noexcept : Pattern(UUID), code(a)   { I_am<Not>(); }
        Not:: Not(const Not &_)    noexcept : Pattern(_), code(_.code) { I_am<Not>(); }

        OutputStream & Not:: viz(OutputStream &fp) const
        {
            nodeName(fp) << '[';
            Label(fp, ASCII::Embedding::Char[code] );
            fp << ",shape=triangle";
            return Endl(fp << ']');
        }

        size_t Not:: serialize(OutputStream &fp) const
        {
            size_t res = fp.emitCBR(uuid);
            fp.write( (char)code );
            return res+1;
        }

        bool Not:: accepts(Token &token, Source &source) const
        {
            assert(0==token.size);
            Char *ch = source.query();
            if(!ch)
                return false;

            if(code == **ch) {
                source.store(ch);
                return false;
            }

            token.pushTail(ch);
            return true;
        }

        FirstChars Not:: firstChars() const noexcept
        {
            FirstChars fc;
            fc.all();
            fc.sub(code);
            return fc;
        }

        bool Not:: strong()   const { return true; }
        bool Not:: univocal() const { return false; }


    }
}
