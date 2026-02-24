#include "y/ink/filter/prewitt7.hpp"

namespace Yttrium
{
    namespace Ink
    {
        const char * const Prewitt7:: Label = "Prewitt7";

        const int8_t Prewitt7:: Table[7][7] =
        {
            { 3,  3,  3,  3,  3,  3,  3},
            { 2,  2,  2,  2,  2,  2,  2},
            { 1,  1,  1,  1,  1,  1,  1},
            { 0,  0,  0,  0,  0,  0,  0},
            {-1, -1, -1, -1, -1, -1, -1},
            {-2, -2, -2, -2, -2, -2, -2},
            {-3, -3, -3, -3, -3, -3, -3}
        };

    }

}
