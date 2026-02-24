



#include "y/ink/filter/scharr5.hpp"

namespace Yttrium
{
    namespace Ink
    {
        const char * const Scharr5:: Label = "Scharr5";

        const int8_t Scharr5:: Table[5][5] =
        {
            {  1,  1,  3,  2,  1 },
            {  1,  2,  6,  2,  1 },
            {  0,  0,  0,  0,  0 },
            { -1, -2, -6, -2, -1 },
            { -1, -1, -3, -2, -1 },
        };

    }

}
