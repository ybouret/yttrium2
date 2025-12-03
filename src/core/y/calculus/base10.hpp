
//! \file

#ifndef Y_Calculus_Base10_Included
#define Y_Calculus_Base10_Included 1

#include "y/type/ints.hpp"
#include <cassert>

namespace Yttrium
{

    template <typename T>
    struct Base10
    {
        static const T Ten = 10;
        static unsigned DigitsFor(T x)
        {
            unsigned count = 1;
            while(x>=Ten) { x/=Ten; ++count; }
            return count;
        }
    };

}

#endif // !Y_Calculus_Base10_Included
