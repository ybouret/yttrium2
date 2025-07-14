#ifndef Y_MKL_Triplet_Included
#define Y_MKL_Triplet_Included 1

#include "y/mkl/api/fabs.hpp"
#include "y/sorting/sort3.hpp"
#include <iostream>

namespace Yttrium
{
    namespace MKL
    {

        template <typename T>
        struct Triplet
        {
            T a;
            T b;
            T c;

            inline size_t size() const noexcept { return 3; }
            inline T *       operator()(void) noexcept { return &a; }
            inline const T * operator()(void) const noexcept { return &a; }

            inline void sort() noexcept
            {
                Sorting::Sort3(&a);
            }

            template <typename U>
            inline void sort(Triplet<U> &peer) noexcept
            {
                Sorting::Sort3(&a,&peer.a);
            }

            inline friend std::ostream & operator<<(std::ostream &os, const Triplet &self)
            {
                return os << '[' << self.a << ';' << self.b << ';' << self.c << ']';
            }

            

        };

    }
}
#endif

