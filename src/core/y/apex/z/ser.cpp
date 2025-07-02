
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
                case __Zero__: fp.write(Mark__Zero__); break;
                case Positive: fp.write(MarkPositive); break;
                case Negative: fp.write(MarkNegative); break;
            }
            return 1+n.serialize(fp);
        }

       



    }

}

