

#include "y/ink/filter/sobel3.hpp"

namespace Yttrium
{
    namespace Ink
    {
        const char * const Sobel3:: Label = "Sobel3";

        const int8_t Sobel3:: Table[3][3] =
        {
            { 1, 2, 1},
            { 0 ,0, 0},
            {-1,-2,-1}
        };

    }

}
