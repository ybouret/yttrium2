#include "y/apex/integer.hpp"
#include "y/stream/output.hpp"
#include "y/stream/input.hpp"
#include "y/exception.hpp"

namespace Yttrium
{

    namespace Apex
    {
        size_t Integer:: serialize(OutputStream &fp) const
        {
            switch(s)
            {
                case __Zero__: fp.write(__Zero__Mark); return 1;
                case Negative: fp.write(NegativeMark); break;
                case Positive: fp.write(PositiveMark); break;
            }
            return 1 + n.serialize(fp);
        }

        Integer:: Integer(InputStream &fp, const char * const varName) :
        s(__Zero__),
        n()
        {
            const char * const id = varName ? varName : "variable";
            char mark = 0x00;
            if(!fp.query(mark)) {
                throw Specific::Exception(CallSign,"no marker for %s",id);
            }

            SignType S = __Zero__;
            switch(mark)
            {
                case __Zero__Mark: return;
                case NegativeMark: S = Negative; break;
                case PositiveMark: S = Positive; break;
                default: throw Specific::Exception(CallSign,"invalid marker for %s",id);
            }

            assert(__Zero__!=S);
            Natural N(fp,varName);
            if(N.bits()<=0) throw Specific::Exception(CallSign,"Zero bits read after %s sign", Sign::HumanReadable(S));

            Coerce(s) = S;
            Coerce(n).xch(N);

        }
    }

}

