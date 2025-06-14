//! \file

#ifndef Y_Pointer_Smart_Included
#define Y_Pointer_Smart_Included 1

#include "y/pointer/immediate.hpp"
#include <cassert>
#include <iostream>

namespace Yttrium
{
    namespace Smart
    {
        template <
        typename T,
        template <typename> class Redirect = Immediate
        >
        class Pointer : public Redirect<T>
        {
        public:
            Y_ARGS_EXPOSE(T,Type);

            inline Type      & operator*()       noexcept { assert(0!=pointee); return *pointee; }
            inline ConstType & operator*() const noexcept { assert(0!=pointee); return *pointee; }


        protected:
            inline explicit Pointer(T * const ptr) : Redirect<T>(), pointee( (MutableType*) ptr) {}
            inline virtual ~Pointer() noexcept { assert(0==pointee); }

            inline void xch(Pointer &other) noexcept
            {
                Swap(pointee,other.pointee);
            }

            MutableType * pointee;

        private:
            Y_Disable_Copy_And_Assign(Pointer);
        };

        

    }
}

#endif


