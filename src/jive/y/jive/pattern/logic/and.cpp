
#include "y/jive/pattern/logic/and.hpp"
#include "y/stream/output.hpp"

namespace Yttrium
{
    namespace Jive
    {

        
        And:: And() noexcept : Logic(UUID) { I_am<And>(); }

        And:: And(const And &_) : Logic(_) { I_am<And>();}



        bool And:: accepts(Token &token, Source &source) const
        {
            assert(0==token.size);

            for(const Pattern *op=head;op;op=op->next)
            {
                Token tmp;
                if(op->accepts(tmp,source))
                {
                    token.mergeTail(tmp);
                    continue;
                }

                source.put(token);
                return false;
            }

            return true;

        }

        size_t And:: serialize(OutputStream &fp) const
        {
            const size_t res = fp.emitCBR(uuid);
            return res + srz(fp);
        }

        OutputStream & And:: viz(OutputStream &fp) const
        {
            nodeName(fp) << '[';
            Label(fp, "&&") << ",shape=house";
            Endl( fp << ']');
            return lnk(fp);
        }

        FirstChars And:: firstChars() const noexcept
        {
            FirstChars fc;
            for(const Pattern *op=head;op;op=op->next)
            {
                FirstChars pfc = op->firstChars();
                fc += pfc;
                if(op->strong()) break;
            }
            return fc;
        }

        bool And:: strong() const
        {
            for(const Pattern *op=head;op;op=op->next)
            {
                if(op->strong()) return true;
            }
            return false;
        }

        //! all strong and univocal
        bool And:: univocal() const
        {
            for(const Pattern * op=head;op;op=op->next)
            {
                if(op->feeble())   return false;
                if(op->flexible()) return false;
            }

            return true;
        }
    }

}


