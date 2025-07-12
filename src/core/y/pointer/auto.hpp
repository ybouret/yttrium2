
//! \file

#ifndef Y_Pointer_Auto_Included
#define Y_Pointer_Auto_Included 1

#include "y/pointer/immediate.hpp"
#include "y/pointer/accept-null.hpp"
#include "y/ability/recyclable.hpp"

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //! AutoPtr with unique instance
    //
    //
    //__________________________________________________________________________
    template <
    typename T,
    template <typename> class Redirect = Immediate
    >
    class AutoPtr : public Smart::AcceptNullPointer<T,Redirect>, public Recyclable
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        typedef Smart::AcceptNullPointer<T,Redirect> PointerType; //!< alias
        using PointerType::pointee;

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
        inline AutoPtr(T * const ptr) noexcept : PointerType(ptr) {} //!< setup \param ptr any address
        inline AutoPtr()              noexcept : PointerType(0)   {} //!< cleanup

        //! cleanup
        inline virtual ~AutoPtr() noexcept
        {
            doFree();
        }

        //! keep only one copy \param other another pointer
        inline AutoPtr(const AutoPtr &other) noexcept :
        PointerType(other.pointee), Recyclable()
        {
            if(0!=pointee) {
                Coerce(other).pointee = 0;
            }
        }

        //! keep only one copy \param other another pointer \return *this
        inline AutoPtr & operator=(const AutoPtr &other) noexcept
        {
            if(pointee != other.pointee)
            {
                if(pointee) delete pointee;
                pointee = other.pointee;
                Coerce(other.pointee) = 0;
            }
            return *this;
        }

        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________

        //! free pointee
        inline virtual void free() noexcept { doFree(); }

        //! \return pointee back to user
        inline T *  yield() noexcept {
            T * const res = pointee;
            pointee = 0;
            return res;
        }

    private:

        //! delete pointee if needed
        inline void doFree() noexcept
        { if(pointee) { delete pointee; pointee=0; } }

    };

}

#endif
