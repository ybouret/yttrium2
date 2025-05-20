//! \file

#ifndef Y_Core_Setup_Included
#define Y_Core_Setup_Included 1

#include "y/system/types.hpp"
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

