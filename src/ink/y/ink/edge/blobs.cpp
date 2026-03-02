
#include "y/ink/edge/blobs.hpp"

namespace Yttrium
{
    namespace Ink
    {
        const unit_t Blobs:: Delta[8][2] =
        {
            // axis
            {  1,  0 },
            {  0,  1 },
            { -1,  0 },
            {  0, -1 },
            // diag
            {  1,  1 },
            { -1,  1 },
            { -1, -1 },
            {  1, -1 }
        };
    }

}
