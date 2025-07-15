
//! \file

#ifndef Y_Core_Utils_Included
#define Y_Core_Utils_Included 1



namespace Yttrium
{
    //__________________________________________________________________________
    //
    //
    //! inline Max
    /**
     \param a lhs argument
     \param b rhs argument
     \return max of a and b
     */
    //
    //__________________________________________________________________________
    template <typename T> inline
    T Max(const T a, const T b)
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
    //! inline Min
    /**
     \param a lhs argument
     \param b rhs argument
     \return min of a and b
     */
    //
    //__________________________________________________________________________
    template <typename T> inline
    T Min(const T a, const T b)
    {
        return a < b ? a : b;
    }

    //__________________________________________________________________________
    //
    //
    //! inline in-situ Min
    /**
     \param a target value
     \param b compared value
     */
    //
    //__________________________________________________________________________
    template <typename T> inline
    void InSituMin(T &a, const T b)
    {
        if(b<a) a = b;
    }

    //__________________________________________________________________________
    //
    //
    //! Clamp integral values
    /**
     \param a lower bound
     \param b test value
     \param c upper bound
     \return MinOf( MaxOf(a,b), c )
     */
    //
    //__________________________________________________________________________
    template <typename T> inline
    T Clamp(const T a, const T b, const T c)
    {
        return Min( Max(a,b), c );
    }

    //! \return a+a \param a any valid type
    template <typename T> inline
    T Twice(const T a)
    {
        return a+a;
    }

    //! \return a*a \param a any valid type
    template <typename T> inline
    T Squared(const T a)
    {
        return a*a;
    }

}

#endif

