#include "y/apex/integer.hpp"
#include "y/stream/output.hpp"

namespace Yttrium
{

    namespace Apex
    {
        size_t Integer:: serialize(OutputStream &fp) const
        {
            switch(s)
            {
                case __Zero__: fp.write(__Zero__Mark); return 1;
                case Negative: fp.write(PositiveMark); break;
                case Positive: fp.write(NegativeMark); break;
            }
            return 1 + n.serialize(fp);
        }
    }

}

