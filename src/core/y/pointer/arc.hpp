
//! \file

#ifndef Y_Pointer_Arc_Included
#define Y_Pointer_Arc_Included 1

#include "y/pointer/reject-null.hpp"

namespace Yttrium
{

    //! common info for ArcPtr
    struct ArcPtrInfo
    {
        static const char * const Name; //!< "ArcPtr"
    };


    //__________________________________________________________________________
    //
    //
    //
    //! A Reference Counting PoinTeR
    //
    //
    //__________________________________________________________________________
    template <typename T,
    template <typename> class Redirect = Immediate
    >
    class ArcPtr : public Smart::RejectNullPointer<T,Redirect>
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        typedef Smart::RejectNullPointer<T,Redirect> PointerType; //!< alias
        using PointerType::pointee;

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________

        //! setup \param ptr valid address
        inline ArcPtr(T * const ptr) : PointerType(ArcPtrInfo::Name,ptr)
        {
            assert(0!=pointee);
            pointee->withhold();
        }

        //! duplicate
        /**
         increase ref count
         \param other another pointer
         */
        inline ArcPtr(const ArcPtr &other) noexcept :
        PointerType(ArcPtrInfo::Name,other.pointee)
        {
            assert(0!=pointee);
            pointee->withhold();
        }


        //! assign by copy/xch \param other another pointer \return *this
        inline ArcPtr & operator=(const ArcPtr &other) noexcept
        {
            ArcPtr temp(other);
            this->xch(temp);
            return *this;
        }

        //! cleanup, delete when ref count is zero
        virtual ~ArcPtr() noexcept
        {
            assert(0!=pointee);
            if(pointee->liberate()) delete pointee;
            pointee = 0;
        }

    };

}

#endif // !Y_Pointer_Arc_Included
