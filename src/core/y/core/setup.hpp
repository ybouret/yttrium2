//! \file


#ifndef Y_Core_Setup_Included
#define Y_Core_Setup_Included 1



namespace Yttrium
{

    template <int N>
    struct IntToType
    {
        enum { Value = N };
    };

    template <typename T>
    struct TypeToType
    {
        typedef T Type;
    };

#define Y_Disable_Copy(CLASS)   private: CLASS(const CLASS &)
#define Y_Disable_Assign(CLASS) private: CLASS & operator=(const CLASS & )
#define Y_Disable_Copy_And_Assign(CLASS) \
/**/ Y_Disable_Copy(CLASS);              \
/**/ Y_Disable_Assign(CLASS)

}

#endif

