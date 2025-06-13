

#ifndef Y_Sorting_Types_Included
#define Y_Sorting_Types_Included 1

#include "y/system/compiler.hpp"
#include <cassert>

namespace Yttrium{

    namespace Sorting
    {

        typedef int (*Compare)(const void * const, const void * const, void * const);

        template <typename T, typename COMPARE>
        struct CompareWrapper
        {
            static inline int Call(const void * const lhs, const void * const rhs, void * const args)
            {
                assert(0!=lhs); assert(0!=rhs); assert(0!=args);
                COMPARE &cmp = *(COMPARE *)args;
                return int( cmp( *(const T*)lhs, *(const T*)rhs));
            }
        };

    }

}

#endif

