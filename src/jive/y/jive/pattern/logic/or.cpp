

#include "y/jive/pattern/logic/or.hpp"
#include "y/stream/output.hpp"

namespace Yttrium
{
    namespace Jive
    {


        Or:: Or() noexcept : Logic(UUID) { I_am<Or>(); }

        Or:: Or(const Or &_) : Logic(_) { I_am<Or>();}


        bool Or:: accepts(Token &token, Source &source) const
        {
            assert(0==token.size);
            bool result = false;
            //std::cerr << "<OR>" << std::endl;
            for(const Pattern *p=head;p;p=p->next)
            {
                if(p->accepts(token,source))
                {
                    //std::cerr << "accepting '" << token << "'" << std::endl;
                    if(token.size>0) return true;
                    assert(p->feeble());
                    result = true; // but leave another chance to strong pattern
                }
            }
            //std::cerr << "<OR/>" << std::endl;

            assert(0==token.size);
            return result;

        }

        size_t Or:: serialize(OutputStream &fp) const
        {
            const size_t res = fp.emitCBR(uuid);
            return res + srz(fp);
        }

        OutputStream & Or:: viz(OutputStream &fp) const
        {
            nodeName(fp) << '[';
            Label(fp, "||") << ",shape=egg";
            Endl( fp << ']');
            return lnk(fp);
        }

        FirstChars Or:: firstChars() const noexcept
        {
            FirstChars fc;
            for(const Pattern *op=head;op;op=op->next)
            {
                FirstChars pfc = op->firstChars();
                fc += pfc;
            }
            return fc;
        }

        bool Or:: strong() const
        {
            for(const Pattern *p=head;p;p=p->next)
            {
                if(p->feeble()) return false;
            }
            return true;
        }

        bool Or:: univocal() const
        {
            switch(size)
            {
                case 0: return true;
                case 1: return head->univocal();
                default:
                    break;
            }
            return  false;
        }
    }

}


