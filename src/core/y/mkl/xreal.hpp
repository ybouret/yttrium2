
//! \file

#ifndef Y_Type_XReal_Included
#define Y_Type_XReal_Included 1

#include "y/type/sign.hpp"
#include "y/type/shallow.hpp"
#include "y/string/fwd.hpp"
#include <iostream>

namespace Yttrium
{
    //__________________________________________________________________________
    //
    //
    //! global output flag
    //
    //__________________________________________________________________________
    struct XRealOutput
    {
        //! output modes
        enum ModeType
        {
            Default, //!< mantissa^exponent
            Compact  //!< converted to real
        };
        
        static ModeType Mode; //!< global value
    };

    Y_Shallow_Decl(Raised); //!< helper to make arbitrary high/low XReal

    //! helper to implement operators
#define Y_XREAL_BINARY(OP,CALL) \
inline friend XReal   operator OP (const XReal &lhs, const XReal &rhs) { return CALL(lhs,rhs); }                            \
inline friend XReal   operator OP (const T      lhs, const XReal &rhs) { const XReal _(lhs); return CALL(_,rhs); }          \
inline friend XReal   operator OP (const XReal &lhs, const T      rhs) { const XReal _(rhs); return CALL(lhs,_); }          \
inline        XReal & operator OP##=(const XReal &rhs)                 { return (*this=CALL(*this,rhs)); }                  \
inline        XReal & operator OP##=(const T      rhs)                 { const XReal _(rhs); return (*this=CALL(*this,_)); }



    //! helper to implement friend comparisons
#define Y_XREAL_CMP(OP,RESULT) \
inline friend bool operator OP (const XReal &lhs, const XReal &rhs) noexcept { return Compare(lhs,rhs) RESULT; } \
inline friend bool operator OP (const XReal &lhs, const T      rhs) noexcept { return Compare(lhs,rhs) RESULT; } \
inline friend bool operator OP (const T      lhs, const XReal &rhs) noexcept { return Compare(lhs,rhs) RESULT; }

    //__________________________________________________________________________
    //
    //
    //! Extended Real
    //
    //__________________________________________________________________________
    template <typename T>
    class XReal
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        typedef T Type; //!< alias

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
        XReal() noexcept;                                //!< zero
        XReal(const T);                                  //!< decompose
        XReal(const XReal &) noexcept;                   //!< copy
        XReal & operator=(const XReal &) noexcept;       //!< assign \return *this
        XReal & operator=(const T);                      //!< decompose/assign \return *this
        ~XReal() noexcept;                               //!< cleanup
        XReal(const T x, const Raised_ &, const int xp); //!< set to x * radix^xp \param x real \param xp exponent  

        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________

        //! display
        inline friend std::ostream &operator<<(std::ostream &os, const XReal &xr)
        { xr.display(os); return os; }

        //! retrieveing floating point value
        operator T() const;

        void               ldz()           noexcept;   //!< in place set to zero
        void               neg()           noexcept;   //!< in place mantissa sign change
        XReal              abs()     const noexcept;   //!< \return absolute value
        XReal              sqrt()             const;   //!< \return square root
        T                  log()              const;   //!< \return log
        T                  log10()            const;   //!< \return log10
        XReal              pow(const T alpha) const;   //!< \param alpha exponent \return this^alpha
        Core::String<char> str()              const;   //!<  \return "%.15g"

        static Core::String<char> ToString(const XReal &x); //!< \param x xreal \return x.str()


        //______________________________________________________________________
        //
        //
        // operations
        //
        //______________________________________________________________________

#ifndef DOXYGEN_SHOULD_SKIP_THIS
        Y_XREAL_BINARY(*,Mul)
        Y_XREAL_BINARY(/,Div)
        Y_XREAL_BINARY(+,Add)
        Y_XREAL_BINARY(-,Sub)
#endif

        XReal operator+() const noexcept; //!< unary + \return   *this
        XReal operator-() const noexcept; //!< unary - \return - *this


        //______________________________________________________________________
        //
        //
        // comparisons
        //
        //______________________________________________________________________
        static SignType Compare(const XReal &, const XReal &) noexcept; //!< \return comparison
        static SignType Compare(const XReal &, const T      ) noexcept; //!< \return comparison
        static SignType Compare(const T      , const XReal &) noexcept; //!< \return comparison

#ifndef DOXYGEN_SHOULD_SKIP_THIS
        Y_XREAL_CMP(==,  == __Zero__ )
        Y_XREAL_CMP(!=,  != __Zero__ )
        Y_XREAL_CMP(<,   == Negative )
        Y_XREAL_CMP(>,   == Positive )
        Y_XREAL_CMP(<=,  != Positive )
        Y_XREAL_CMP(>=,  != Negative )
#endif

        //______________________________________________________________________
        //
        //
        // Other
        //
        //______________________________________________________________________
        T p() const; //!< \return -log10(*this)


        //______________________________________________________________________
        //
        //
        // members
        //
        //______________________________________________________________________
        const int exponent; //!< exponent
        const T   mantissa; //!< mantissa

    private:
        explicit XReal(const int, const T) noexcept;             //!< manual setup
        static XReal Mul(const XReal &, const XReal &) noexcept; //!< \return mutliplication
        static XReal Div(const XReal &, const XReal &);          //!< \return division
        static XReal Add(const XReal &, const XReal &);          //!< \return addition
        static XReal Sub(const XReal &, const XReal &);          //!< \return subtraction
        void   display(std::ostream &) const;                    //!< display
    };

}

#endif

