
//! \file

#ifndef Y_Pointer_Arc_Included
#define Y_Pointer_Arc_Included 1

#include "y/pointer/reject-null.hpp"

namespace Yttrium
{
    struct ArcPtrInfo
    {
        static const char * const Name;
    };


    template <typename T,
    template <typename> class Redirect = Immediate
    >
    class ArcPtr : public Smart::RejectNullPointer<T,Redirect>
    {
    public:
        typedef Smart::RejectNullPointer<T,Redirect> PointerType;
        using PointerType::pointee;

        inline ArcPtr(T * const ptr) : PointerType(ArcPtrInfo::Name,ptr)
        {
            assert(0!=pointee);
            pointee->withhold();
        }

        inline ArcPtr(const ArcPtr &other) noexcept :
        PointerType(ArcPtrInfo::Name,other.pointee)
        {
            assert(0!=pointee);
            pointee->withhold();
        }

        inline ArcPtr & operator=(const ArcPtr &other) noexcept
        {
            ArcPtr temp(other);
            xch(temp);
            return *this;
        }


        virtual ~ArcPtr() noexcept
        {
            assert(0!=pointee);
            if(pointee->liberate()) delete pointee;
            pointee = 0;
        }

    };

}

#endif
