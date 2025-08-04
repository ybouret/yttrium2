

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
            for(const Pattern *op=ops.head;op;op=op->next)
            {
                FirstChars pfc = op->firstChars();
                fc += pfc;
            }
            return fc;
        }

        bool Or:: strong() const
        {

        }

        //! all strong and univocal
        bool Or:: univocal() const
        {

        }
    }

}


