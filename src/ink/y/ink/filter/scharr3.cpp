


#include "y/ink/filter/scharr3.hpp"

namespace Yttrium
{
    namespace Ink
    {
        const char * const Scharr3:: Label = "Scharr3";

        const int8_t Scharr3:: Table[3][3] =
        {
            { 1, 3, 1},
            { 0 ,0, 0},
            {-1,-3,-1}
        };

    }

}
