
//! \file

#ifndef Y_Type_Complex_Included
#define Y_Type_Complex_Included 1

#include "y/type/sign.hpp"
#include "y/mkl/api/pythagoras.hpp"
#include <iostream>

namespace Yttrium
{
    namespace Core
    {
        //! common data for complexes
        struct Complex
        {
            static const char LPAREN = '('; //!< alias
            static const char RPAREN = ')'; //!< alias
            static const char PLUS   = '+'; //!< alias
            static const char IM[4];        //!< "im"
        };
    }
    //__________________________________________________________________________
    //
    //
    //! Complex number
    //
    //__________________________________________________________________________
    template <typename T>
    class Complex
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        typedef T             Type; //!< alias
        typedef Core::Complex Self; //!< alias
        static const size_t   DIMENSIONS = 2; //!< alias

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
        inline Complex()                     noexcept : re(0), im(0)       {} //!< zero
        inline Complex(const T x)            noexcept : re(x), im(0)       {} //!< from scalar \param x re
        inline Complex(const T x, const T y) noexcept : re(x), im(y)       {} //!< from scalars \param x re \param y im
        inline Complex(const Complex &z)     noexcept : re(z.re), im(z.im) {} //!< from complex \param z complex
        inline ~Complex()                    noexcept                      {} //!< cleanup

        inline Complex &operator=(const Complex z) noexcept { re=z.re; im=z.im; return *this; } //!< assign \param z complex \return *this
        inline Complex &operator=(const T       x) noexcept { re=x;    im=0;    return *this; } //!< assign \param x scalar  \return *this

        //______________________________________________________________________
        //
        //
        // Pseudo-API
        //
        //______________________________________________________________________

        //! \return DIMENSIONS
        inline size_t size()            const noexcept { return DIMENSIONS; }

        //! \param indx [1..2] \return re or im
        inline T &    operator[](size_t indx) noexcept {
            assert(indx>=1); assert(indx<=2);
            return *(&re + --indx);
        }

        //! \param indx [1..2] \return re or im
        inline const T &    operator[](size_t indx) const noexcept {
            assert(indx>=1); assert(indx<=2);
            return *(&re + --indx);
        }

        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________

        //! no-throw exchange \param z complex \return *this*
        inline Complex & xch( Complex &z ) noexcept { Swap(re,z.re); Swap(im,z.im); return *this; }

        //! display
        friend std::ostream & operator<<(std::ostream &os, const Complex &z)
        {
            os << Self::LPAREN << z.re << Self::PLUS << Self::LPAREN << z.im << Self::IM << Self::RPAREN << Self::RPAREN;
            return os;
        }

        inline Complex conj() const noexcept { return Complex(re,-im); }        //!< \return conjugate
        inline T       mod2() const noexcept { return im*im + re*re;   }        //!< \return |z|^2
        inline T       abs()  const noexcept { return MKL::Pythagoras(re,im); } //!< \return |z|

        //______________________________________________________________________
        //
        //
        // Add
        //
        //______________________________________________________________________

        //! unary plus \return *this
        inline Complex operator+() const noexcept { return Complex(re,im); }

        //! \param lhs complex \param rhs complex \return lhs+rhs
        friend inline Complex operator+(const Complex &lhs, const Complex &rhs) noexcept
        { return Complex(lhs.re+rhs.re,lhs.im+rhs.im); }

        //! \param lhs complex \param rhs scalar \return lhs+rhs
        friend inline Complex operator+(const Complex &lhs, const T rhs) noexcept
        { return Complex(lhs.re+rhs,lhs.im); }

        //! \param lhs scalar \param rhs complex \return lhs+rhs
        friend inline Complex operator+(const T  lhs, const Complex &rhs) noexcept
        { return Complex(lhs+rhs.re,rhs.im); }

        //! \param z complex \return *this + z
        inline Complex & operator+=(const Complex &z) noexcept
        { re += z.re; im += z.im; return *this; }

        //! \param x scalar \return *this + x
        inline Complex & operator+=(const T x) noexcept
        { re += x; return *this; }



        //______________________________________________________________________
        //
        //
        // Sub
        //
        //______________________________________________________________________

        //! unary minus \return - (*this)
        inline Complex operator-() const noexcept { return Complex(-re,-im); }

        //! \param lhs complex \param rhs complex \return lhs-rhs
        friend inline Complex operator-(const Complex &lhs, const Complex &rhs) noexcept
        { return Complex(lhs.re-rhs.re,lhs.im-rhs.im); }

        //! \param lhs complex \param rhs scalar \return lhs-rhs
        friend inline Complex operator-(const Complex &lhs, const T rhs) noexcept
        { return Complex(lhs.re-rhs,lhs.im); }

        //! \param lhs scalar \param rhs complex \return lhs-rhs
        friend inline Complex operator-(const T  lhs, const Complex &rhs) noexcept
        { return Complex(lhs-rhs.re,-rhs.im); }

        //! \param z complex \return (*this) -= z
        inline Complex & operator-=(const Complex &z) noexcept
        { re -= z.re; im -= z.im; return *this; }

        //! \param x scalar \return (*this) -= x
        inline Complex & operator-=(const T x) noexcept
        { re -= x; return *this; }

        //______________________________________________________________________
        //
        //
        // Mul
        //
        //______________________________________________________________________


        //! \return z*x
        inline friend Complex operator*(const Complex &z, const T x) noexcept
        { return Complex(z.re*x,z.im*x); }

        //! \return x*z
        inline friend Complex operator*(const T x, const Complex &z) noexcept
        { return Complex(z.re*x,z.im*x); }

        //! standard multiplication \param X lhs \param Y lhs \return X*Y
        inline static Complex MultiAlgo(const Complex &X, const Complex &Y) noexcept
        { return Complex(X.re * Y.re - X.im * Y.im, X.re * Y.im + X.im * Y.re); }

        //! Gauss' multiplication \param X lhs \param Y lhs \return X*Y
        inline static Complex GaussAlgo(const Complex &X, const Complex &Y) noexcept
        {
            const T S1 = X.re * Y.re;
            const T S2 = X.im * Y.im;
            const T S3 = (X.re+X.im) * (Y.re+Y.im);
            return Complex(S1-S2,S3-S1-S2);
        }

        //! \return X*Y
        inline friend Complex operator*(const Complex &X, const Complex &Y) noexcept
        { return Complex(X.re * Y.re - X.im * Y.im, X.re * Y.im + X.im * Y.re); }

        //! \param x scalar \return (*this) *= x
        inline Complex & operator*=(const T x)        { re *= x; im *= x; return *this; }

        //! \param z complex \return (*this) *= z
        inline Complex & operator*=(const Complex &z)
        { const Complex p = (*this) * z; re=p.re; im=p.im; return *this; }

        //______________________________________________________________________
        //
        //
        // Division
        //
        //______________________________________________________________________

        //! z/x
        inline friend Complex operator/(const Complex &z, const T x)
        {
            // TODO: check
            return Complex(z.re/x,z.im/x);
        }

        //! x/z
        inline friend Complex operator/(const T x, const Complex &z)
        {
            return (x*z.conj())/z.mod2();
        }

        //! X/Y
        inline friend Complex operator/(const Complex &X, const Complex &Y)
        {
            return (X * Y.conj())/Y.mod2();
        }

        //! \param x scalar \return (*this) /= x
        inline Complex & operator/=(const T x)        { re/=x; im/=x; return *this; }

        //! \param z complex \return (*this) /= z
        inline Complex & operator/=(const Complex &z)
        {
            const Complex d = (*this) / z; re = d.re; im = d.im; return *this;
        }

        //______________________________________________________________________
        //
        //
        // comparison
        //
        //______________________________________________________________________

        //! testing equality, TODO
        friend inline bool operator==(const Complex &lhs, const Complex &rhs) noexcept
        {
            return lhs.re == rhs.re && lhs.im == rhs.im;
        }


        //! testing difference
        friend inline bool operator!=(const Complex &lhs, const Complex &rhs) noexcept
        {
            return lhs.re != rhs.re || lhs.im != rhs.im;
        }


        //______________________________________________________________________
        //
        //
        // Members
        //
        //______________________________________________________________________
        

        T re; //!< real part
        T im; //!< imaginary part
    };
}

#endif
