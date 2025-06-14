
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



    private:

    };

}

#endif
