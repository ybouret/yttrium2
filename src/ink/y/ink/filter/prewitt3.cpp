
#include "y/ink/filter/prewitt3.hpp"

namespace Yttrium
{
    namespace Ink
    {
        const char * const Prewitt3:: Label = "Prewitt3";
        
        const int8_t Prewitt3:: Table[3][3] =
        {
            { 1, 1, 1},
            { 0 ,0, 0},
            {-1,-1,-1}
        };

    }

}
