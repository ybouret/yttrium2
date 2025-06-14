
//! \file

#ifndef Y_Pointer_Auto_Included
#define Y_Pointer_Auto_Included 1

#include "y/pointer/immediate.hpp"
#include "y/pointer/smart.hpp"

namespace Yttrium
{

    template <
    typename T,
    template <typename> class Redirect = Immediate
    >
    class AutoPtr : public Smart::Pointer<T,Redirect>
    {
    public:
        typedef Smart::Pointer<T,Redirect> PointerType;
        using PointerType::pointee;


        inline AutoPtr(T * const ptr) noexcept : PointerType(ptr) {}
        inline AutoPtr()              noexcept : PointerType(0)   {}

        inline virtual ~AutoPtr() noexcept
        {
            if(pointee) { delete pointee; pointee=0; }
        }

        inline AutoPtr(const AutoPtr &other) noexcept :
        PointerType(other.pointee)
        {
            if(0!=pointee) {
                Coerce(other).pointee = 0;
            }
        }

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

        inline friend std::ostream & operator<<(std::ostream &os, const AutoPtr &self)
        {
            if(self.pointee) os << *self.pointee; else os << Core::Nil;
            return os;
        }

        inline T * yield() noexcept
        {
            T * const res = pointee;
            pointee = 0;
            return res;
        }




    };

}

#endif
