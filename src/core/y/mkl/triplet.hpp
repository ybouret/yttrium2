#ifndef Y_MKL_Triplet_Included
#define Y_MKL_Triplet_Included 1

#include "y/mkl/api/fabs.hpp"
#include "y/sorting/sort3.hpp"
#include <iostream>

namespace Yttrium
{
    namespace MKL
    {

        //______________________________________________________________________
        //
        //
        //! C-style triplet
        //
        //______________________________________________________________________
        template <typename T>
        struct Triplet
        {
            static const size_t DIMENSIONS = 3;

            T a; //!< a value
            T b; //!< b value
            T c; //!< c value

            inline size_t    size()           const noexcept { return DIMENSIONS; } //!< \return 3
            inline T *       operator()(void)       noexcept { return &a; } //!< \return mutable address
            inline const T * operator()(void) const noexcept { return &a; } //!< \return const address
            inline T & operator[](size_t indx) noexcept
            {
                assert(indx>=1);
                assert(indx<=DIMENSIONS);
                return *( (&a) + --indx );
            }

            inline const T & operator[](size_t indx) const noexcept
            {
                assert(indx>=1);
                assert(indx<=DIMENSIONS);
                return *( (&a) + --indx );
            }


            //! sort a <= b <= c
            inline void sort() noexcept
            {
                Sorting::Sort3(&a);
            }

            //! sort a <= b <= c \param peer co-sorted triplet
            template <typename U>
            inline void sort(Triplet<U> &peer) noexcept
            {
                Sorting::Sort3(&a,&peer.a);
            }

            //! display \param os output stream \param self *this \return os
            inline friend std::ostream & operator<<(std::ostream &os, const Triplet &self)
            {
                return os << '[' << self.a << ';' << self.b << ';' << self.c << ']';
            }

            

        };

    }
}
#endif

