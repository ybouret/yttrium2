


#include "y/jive/pattern/logic/none.hpp"
#include "y/stream/output.hpp"

namespace Yttrium
{
    namespace Jive
    {


        None:: None() noexcept : Logic(UUID) { I_am<None>(); }
        None:: None(const None &_) : Logic(_) { I_am<None>();}



        bool None:: accepts(Token &token, Source &source) const
        {
            assert(0==token.size);

            for(const Pattern *p=head;p;p=p->next)
            {
                if(p->accepts(token,source))
                {
                    source.put(token);
                    return false;
                }
            }

            Char * const ch = source.get();

            if(!ch)
                return false;

            token.pushTail(ch);
            return true;

        }

        size_t None:: serialize(OutputStream &fp) const
        {
            const size_t res = fp.emitCBR(uuid);
            return res + srz(fp);
        }

        OutputStream & None:: viz(OutputStream &fp) const
        {
            nodeName(fp) << '[';
            Label(fp, "!!") << ",shape=octagon";
            Endl( fp << ']');
            return lnk(fp);
        }

        FirstChars None:: firstChars() const noexcept
        {
            FirstChars fc;
            fc.all();
            for(const Pattern *op=head;op;op=op->next)
            {
                FirstChars pfc = op->firstChars();
                fc -= pfc;
            }
            return fc;
        }

        bool None:: strong() const
        {
            return true;
        }

        bool None:: univocal() const
        {
            return false;
        }
    }

}


