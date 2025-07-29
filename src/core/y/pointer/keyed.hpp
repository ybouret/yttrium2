//! \file

#ifndef Y_Pointer_Keyed_Included
#define Y_Pointer_Keyed_Included 1

#include "y/type/args.hpp"

namespace Yttrium
{

    template<typename KEY, class PTR>
    class Keyed : public PTR
    {
    public:
        Y_Args_Expose(KEY,Key);
        typedef typename PTR::Type Type;

        inline virtual ~Keyed() noexcept {}

        inline Keyed(Type * const obj) : PTR(obj) {}
        inline Keyed(const Keyed &ptr) : PTR(ptr) {}
        inline Keyed & operator=(const Keyed &ptr)
        {
            PTR &       lhs = *this;
            const PTR & rhs = ptr;
            lhs = rhs;
            return *this;
        }

        inline ConstKey & key() const noexcept { return (**this).key(); }

    };

}

#endif

