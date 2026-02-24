

#include "y/ink/filter/prewitt5.hpp"

namespace Yttrium
{
    namespace Ink
    {
        const char * const Prewitt5:: Label = "Prewitt5";

        const int8_t Prewitt5:: Table[5][5] =
        {
            { 2, 2, 2, 2, 2},
            { 1, 1, 1, 1, 1},
            { 0 ,0, 0, 0, 0},
            {-1,-1,-1,-1,-1},
            {-2,-2,-2,-2,-2}
        };

    }

}
