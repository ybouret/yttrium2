
#include "y/jive/pattern/joker/option.hpp"
#include "y/stream/output.hpp"

namespace Yttrium
{
    namespace Jive
    {

        Option:: Option(const Motif &m) noexcept :
        Joker(UUID,m)
        {
        }

        Option:: Option(const Option &opt) noexcept :
        Joker(opt)
        {
        }


        size_t Option:: serialize(OutputStream &fp) const
        {
            size_t res = fp.emitCBR(uuid);
            return res + motif->serialize(fp);
        }

        bool Option:: accepts(Token &token, Source &source) const
        {
            (void) motif->accepts(token,source);
            return true;
        }


        bool Option:: strong() const { return false; }

        OutputStream & Option:: viz(OutputStream &fp) const
        {
            nodeName(fp) << '[';
            Label(fp,'?') << ",shape=diamond";
            Endl(fp << ']');
            motif->viz(fp);
            return Endl( to( & *motif , fp) );
        }

        FirstChars Option:: firstChars() const noexcept
        {
            return motif->firstChars();
        }


    }

}
