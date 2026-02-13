
//! \file

#ifndef Y_Color_RGBA_Included
#define Y_Color_RGBA_Included

#include "y/color/opaque.hpp"
#include "y/color/print.hpp"
#include <cassert>

namespace Yttrium
{
    namespace Color
    {

        template <typename> class RGB;

        //______________________________________________________________________
        //
        //
        //
        //! RGBA scheme
        //
        //
        //______________________________________________________________________
        template <typename T>
        class RGBA
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const size_t DIMENSIONS = 4; //!< alias

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup black, opaque
            inline RGBA() noexcept : r(0), g(0), b(0), a(Opaque<T>::Value) {}

            //! setup opaque \param R r \param G g \param B b \param A a
            inline RGBA(const T R, const T G, const T B, const T A = Opaque<T>::Value) noexcept : r(R), g(G), b(B), a(A) {}

            //! assign \param c another rgba \return *this
            inline RGBA & operator=(const RGBA &c) noexcept {
                r = c.r;
                g = c.g;
                b = c.b;
                a = c.a;
                return *this;
            }

            //! duplicate \param c another rgba
            inline  RGBA(const RGBA &c) noexcept : r(c.r), g(c.g), b(c.b), a(c.a) {}

            //! cleanup
            inline ~RGBA() noexcept {}

            RGBA(const RGB<T> &c, const T A = Opaque<T>::Value) noexcept; //!< setup \param c rgb \param A a
            RGBA & operator=(const RGB<T> &c)                   noexcept; //!< assign, keep alpha \param c rgb \return *this


            //! display \param os stream \param c color \return os
            inline friend std::ostream & operator<<(std::ostream &os, const RGBA &c)
            {
                Print(os << '(',c.r) << ',';
                Print(os,c.g)        << ',';
                Print(os,c.b)        << ',';
                Print(os,c.a)        << ')';
                return os;
            }

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            inline T &       operator[](const size_t i)       noexcept { assert(i>=1); assert(i<=4);  return *((&r)+i-1); } //!< \param i index \return access[1..2]
            inline const T & operator[](const size_t i) const noexcept { assert(i>=1); assert(i<=4);  return *((&r)+i-1); } //!< \param i index \return access[1..2]


            inline friend bool operator==(const RGBA &x, const RGBA &y) noexcept
            {
                return (x.r == y.r) && (x.g == y.g) && (x.b == y.b) && (x.a==y.a);
            }

            inline friend bool operator!=(const RGBA &x, const RGBA &y) noexcept
            {
                return (x.r != y.r) || (x.g != y.g) || (x.b != y.b) || (x.a != y.a);
            }

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            T r; //!< red
            T g; //!< blue
            T b; //!< green
            T a; //!< alpha
        };
    }
}


#endif // !Y_Color_RGBA_Included
