#ifndef Y_MKL_Triplet_Included
#define Y_MKL_Triplet_Included 1

#include "y/mkl/api/fabs.hpp"
#include "y/mkl/api/half.hpp"
#include "y/sorting/sort3.hpp"
#include "y/core/utils.hpp"
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
            static const size_t DIMENSIONS = 3; //!< pseudo-dimension

            T a; //!< a value
            T b; //!< b value
            T c; //!< c value

            inline size_t    size()           const noexcept { return DIMENSIONS; } //!< \return 3
            inline T *       operator()(void)       noexcept { return &a; } //!< \return mutable address
            inline const T * operator()(void) const noexcept { return &a; } //!< \return const address

            //! \param indx in [1..DIMENSIONS] \return matching value
            inline T & operator[](size_t indx) noexcept
            {
                assert(indx>=1);
                assert(indx<=DIMENSIONS);
                return *( (&a) + --indx );
            }

            //! \param indx in [1..DIMENSIONS] \return matching value
            inline const T & operator[](size_t indx) const noexcept
            {
                assert(indx>=1);
                assert(indx<=DIMENSIONS);
                return *( (&a) + --indx );
            }

            //! \return a <= b && b <= c;
            inline bool isIncreasing() const
            {
                return a <= b && b <= c;
            }

            //! \return c <= b && b <= a
            inline bool isDecreasing() const
            {
                return c <= b && b <= a;
            }

            //! \return increasing or decreasing
            inline bool isOrdered() const
            {
                return isIncreasing() || isDecreasing();
            }

            //! sort a <= b <= c
            inline void sort() noexcept
            {
                Sorting::Sort3(&a); assert(isIncreasing());
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

            //! \return maximum amplitude
            inline T amplitude() const
            {
                return Max( Fabs<T>::Of(a-b), Fabs<T>::Of(a-c), Fabs<T>::Of(b-c) );
            }

            //! \return |c-a|
            inline T width() const
            {
                const T delta = c - a;
                return Fabs<T>::Of(delta);
            }


            //! \return b <= a && b <= c
            inline bool isLocalMinimum() const
            {
                return b <= a && b <= c;
            }

            inline T middle() const
            {
                return Half<T>::Of(a,c);
            }

            inline void save( T data[] ) const
            {
                data[0] = a;
                data[1] = b;
                data[2] = c;
            }

            inline void load( const T data[] )
            {
                a = data[0];
                b = data[1];
                c = data[2];
            }



        };

    }
}
#endif

