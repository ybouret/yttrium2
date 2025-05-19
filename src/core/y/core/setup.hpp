//! \file

#ifndef Y_Core_Setup_Included
#define Y_Core_Setup_Included 1

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

}

#endif

