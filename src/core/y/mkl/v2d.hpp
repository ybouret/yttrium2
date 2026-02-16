
//! \file

#ifndef Y_MKL_V2D_Included
#define Y_MKL_V2D_Included 1

#include "y/mkl/api/pythagoras.hpp"
#include "y/core/utils.hpp"
#include <iostream>
#include <cmath>

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //! 2D Vertex
    //
    //
    //__________________________________________________________________________
    template <typename T>
    class V2D
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definition
        //
        //______________________________________________________________________
        typedef T             Type; //!< alias
        static const size_t   DIMENSIONS = 2; //!< alias
        
        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
        inline  V2D()                         noexcept : x(0), y(0) {}                 //!< setup 0
        inline  V2D(const T X, const T Y)     noexcept : x(X), y(Y) {}                 //!< setup \param X x \param Y y
        inline ~V2D()                         noexcept {}                              //!< cleanup
        inline  V2D(const V2D &v)             noexcept : x(v.x), y(v.y) {}             //!< duplicate \param v another vertex
        inline  V2D & operator=(const V2D &v) noexcept { x=v.x; y=v.y; return *this; } //!< assign    \param v another vertex \return *this

        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________

        //! pseudo writable \return 2
        inline size_t size() const noexcept { return 2; }

        //______________________________________________________________________
        //
        // access
        //______________________________________________________________________
        inline T &       operator[](const size_t i)       noexcept { assert(i==1||i==2); return *((&x)+i-1); } //!< \param i index \return access[1..2]
        inline const T & operator[](const size_t i) const noexcept { assert(i==1||i==2); return *((&x)+i-1); } //!< \param i index \return access[1..2]

        //______________________________________________________________________
        //
        // addition
        //______________________________________________________________________
        inline V2D        operator+()                         const noexcept { return V2D(x,y); }                     //!< unary + \return *this
        inline friend V2D operator+(const V2D &lhs, const V2D &rhs) noexcept { return V2D(lhs.x+rhs.x,lhs.y+rhs.y); } //!< binary +
        inline V2D & operator+=(const V2D &rhs)                     noexcept { x+=rhs.x; y+=rhs.y; return *this; }    //!< \param rhs rhs  \return *this+rhs

        //______________________________________________________________________
        //
        // subtraction
        //______________________________________________________________________
        inline V2D        operator-()                         const noexcept { return V2D(-x,-y); }                   //!< unary - \return -(*this)
        inline friend V2D operator-(const V2D &lhs, const V2D &rhs) noexcept { return V2D(lhs.x-rhs.x,lhs.y-rhs.y); } //!< binary -
        inline V2D & operator-=(const V2D &rhs)                     noexcept { x-=rhs.x; y-=rhs.y; return *this; }    //!< \param rhs rhs  \return *this-rhs

        //______________________________________________________________________
        //
        // multiplication
        //______________________________________________________________________
        inline friend V2D operator*(const T u, const V2D &v)    noexcept { return V2D(v.x*u,v.y*u);  } //!< left multiplication
        inline V2D &      operator*=(const T u)                 noexcept { x*=u; y*=u; return *this; } //!< \param u scalar \return u * *this
        inline friend T   operator*(const V2D &a, const V2D &b) noexcept { return a.x*b.x + a.y*b.y; } //!< dot product

        //______________________________________________________________________
        //
        // division
        //______________________________________________________________________
        inline friend V2D operator/( const V2D &v, const T u)   noexcept { return V2D(v.x/u,v.y/u);  } //!< right division
        inline V2D &      operator/=(const T u)                 noexcept { x/=u; y/=u; return *this; } //!< \param u scalar \return (1/u) * *this*


        //______________________________________________________________________
        //
        //! display
        //______________________________________________________________________
        inline friend std::ostream & operator<<(std::ostream &os, const V2D &v)
        { return os << '[' << v.x << ';' << v.y << ']';         }

        //______________________________________________________________________
        //
        //! equality
        //______________________________________________________________________
        inline friend bool operator==(const V2D &lhs, const V2D &rhs) noexcept
        {
            return lhs.x == rhs.x && lhs.y == rhs.y;
        }

        //______________________________________________________________________
        //
        //! difference
        //______________________________________________________________________
        inline friend bool operator!=(const V2D &lhs, const V2D &rhs) noexcept
        {
            return lhs.x != rhs.x || lhs.y != rhs.y;
        }

        //______________________________________________________________________
        //
        //! \return |v|^2
        //______________________________________________________________________
        inline T norm2() const noexcept
        {
            return x*x + y*y;
        }

        //______________________________________________________________________
        //
        //! \return |v|
        //______________________________________________________________________
        inline T norm() const noexcept
        {
            return MKL::Pythagoras(x,y);
        }

        //! \return lower point \param lhs lhs \param rhs rhs
        inline static V2D MinOf(const V2D &lhs, const V2D &rhs) noexcept
        {
            return V2D(Min(lhs.x,rhs.x),Min(lhs.y,rhs.y));
        }

        //! \return upper point \param lhs lhs \param rhs rhs
        inline static V2D MaxOf(const V2D &lhs, const V2D &rhs) noexcept
        {
            return V2D(Max(lhs.x,rhs.x),Max(lhs.y,rhs.y));
        }

        //! \return direct orthogonal rotation
        inline V2D ortho() const noexcept
        {
            return V2D(-y,x);
        }

        //! \return transpose
        inline V2D transpose() const noexcept
        {
            return V2D(y,x);
        }

        //______________________________________________________________________
        //
        //
        // Members
        //
        //______________________________________________________________________
        T x; //!< first
        T y; //!< second
    };

}

#endif // !Y_MKL_V2D_Included

