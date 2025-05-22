//! \file

#ifndef Y_Core_Setup_Included
#define Y_Core_Setup_Included 1

#include "y/system/compiler.hpp"
#include <iosfwd>

namespace Yttrium
{
    //__________________________________________________________________________
    //
    //
    //
    //! helper to convert an integer into a class
    //
    //
    //__________________________________________________________________________
    template <int N>
    struct IntToType
    {
        enum
        {
            Value = N //!< identifier
        };
    };


    //__________________________________________________________________________
    //
    //
    //
    //! helper to convert a type into a class
    //
    //
    //__________________________________________________________________________
    template <typename T>
    struct TypeToType
    {
        typedef T Type; //!< identifier
    };


    //__________________________________________________________________________
    //
    //
    //
    //! set mutability
    /**
     \param obj target object
     \return mutable obj
     */
    //
    //__________________________________________________________________________
    template <typename T> inline
    T & Coerce(const T &obj) noexcept {
        return (T&)obj;
    }

    //__________________________________________________________________________
    //
    //
    //! C-style swap
    /**
     \param lhs first object
     \param rhs second object
     */
    //
    //__________________________________________________________________________
    template <typename T> inline
    void Swap(T &lhs, T &rhs)
    {
        const T tmp(rhs);
        rhs = lhs;
        lhs = tmp;
    }

    //__________________________________________________________________________
    //
    //
    //! force C-style swap
    /**
     \param lhs first object
     \param rhs second object
     */
    //
    //__________________________________________________________________________
    template <typename T> inline
    void CoerceSwap(const T &lhs, const T &rhs)
    {
        const T tmp(rhs);
        Coerce(rhs) = lhs;
        Coerce(lhs) = tmp;
    }

    //__________________________________________________________________________
    //
    //
    //! privatize copy constructor
    //
    //__________________________________________________________________________
#define Y_Disable_Copy(CLASS)   private: CLASS(const CLASS &)

    //__________________________________________________________________________
    //
    //
    //! privatize assigment
    //
    //__________________________________________________________________________
#define Y_Disable_Assign(CLASS) private: CLASS & operator=(const CLASS & )

    //__________________________________________________________________________
    //
    //
    //! privatize both copy and assign
    //
    //__________________________________________________________________________
#define Y_Disable_Copy_And_Assign(CLASS) \
/**/ Y_Disable_Copy(CLASS);              \
/**/ Y_Disable_Assign(CLASS)


    namespace Core
    {
        extern const char * const Success; //!< "Success"
        extern const char * const Failure; //!< "Failure"
        extern const char * const Unknown; //!< "Unknown"

        //______________________________________________________________________
        //
        //
        //! Indent or Make a line of separator
        /**
         \param os        output stream
         \param count     number of repetitions
         \param separator single char separator
         \return os
         */
        //
        //______________________________________________________________________
        std::ostream & Indent(std::ostream & os,
                              size_t         count,
                              const char     separator=' ');
    }
}

#endif

