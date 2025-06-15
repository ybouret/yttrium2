
//! \file

#ifndef Y_Pointer_FlashLock_Included
#define Y_Pointer_FlashLock_Included 1

#include "y/type/args.hpp"
#include <cassert>

namespace Yttrium
{

    template <class T> class LockingProxy
    {
    public:
        Y_ARGS_EXPOSE(T,Type);
        inline LockingProxy(T * const ptr) : pointee((MutableType*)ptr)
        {
            assert(0!=pointee);
            pointee->lock();
        }

        inline ~LockingProxy() noexcept {
            assert(0!=pointee);
            pointee->unlock();
        }

        inline Type * operator->() noexcept {
            assert(0!=pointee);
            return pointee;
        }

        inline LockingProxy(const LockingProxy &other) noexcept :
        pointee(other.pointee)
        {
        }




    private:
        Y_Disable_Assign(LockingProxy);
        MutableType * const pointee;
    };

    template <class T> class FlashLock
    {
    public:
        Y_ARGS_EXPOSE(T,Type);
        typedef LockingProxy<Type>      ReturnType;
        typedef LockingProxy<ConstType> ConstReturnType;


        inline virtual ~FlashLock() noexcept {}
    protected:
        inline explicit FlashLock() noexcept {}

        inline ReturnType      fetch(Type      *ptr)       noexcept { assert(0!=ptr); return ReturnType(ptr); }
        inline ConstReturnType fetch(ConstType *ptr) const noexcept { assert(0!=ptr); return ConstReturnType(ptr); }

    private:
        Y_Disable_Copy_And_Assign(FlashLock);
    };


}

#endif
