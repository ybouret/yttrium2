


#include "y/ink/filter/sobel5.hpp"

namespace Yttrium
{
    namespace Ink
    {
        const char * const Sobel5:: Label = "Sobel5";

        const int8_t Sobel5:: Table[5][5] =
        {
            {   5,   8,  10,   8,  5 },
            {   4,  10,  20,  10,  4 },
            {   0,   0,   0,   0,  0 },
            {  -4, -10, -20, -10, -4 },
            {  -5,  -8, -10,  -8, -5 },
        };

    }

}
