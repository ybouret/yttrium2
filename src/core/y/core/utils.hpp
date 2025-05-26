
//! \file

#ifndef Y_Core_Utils_Included
#define Y_Core_Utils_Included 1



namespace Yttrium
{
    //__________________________________________________________________________
    //
    //
    //! inline MaxOf
    /**
     \param a lhs argument
     \param b rhs argument
     \return max of a and b
     */
    //
    //__________________________________________________________________________
    template <typename T> inline
    T MaxOf(const T a, const T b)
    {
        return a < b ? b : a;
    }

    //__________________________________________________________________________
    //
    //
    //! inline in-situ Max
    /**
     \param a target value
     \param b compared value
     */
    //
    //__________________________________________________________________________
    template <typename T> inline
    void InSituMax(T &a, const T b)
    {
        if(a<b) a = b;
    }

    //__________________________________________________________________________
    //
    //
    //! inline MinOf
    /**
     \param a lhs argument
     \param b rhs argument
     \return min of a and b
     */
    //
    //__________________________________________________________________________
    template <typename T> inline
    T MinOf(const T a, const T b)
    {
        return a < b ? a : b;
    }


    template <typename T> inline
    T Clamp(const T a, const T b, const T c)
    {
        return MinOf( MaxOf(a,b), c );
    }

}

#endif

