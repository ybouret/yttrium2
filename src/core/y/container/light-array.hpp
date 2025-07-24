
//! \file

#ifndef Y_Ligth_Array_Included
#define Y_Light_Array_Included 1

#include "y/container/contiguous.hpp"
#include "y/check/usual.hpp"
#include "y/memory/stealth.hpp"

namespace Yttrium
{

    template <typename T>
    class LightArray : public Contiguous< Writable<T> >
    {
    public:
        Y_Args_Expose(T,Type);
        typedef Contiguous< Writable<T> > SelfType;

        inline LightArray(Type * const arr, const size_t num) noexcept :
        SelfType(),
        cxx( ((MutableType *) Memory::Stealth::Address(arr))-1 ),
        count(num)
        {
            assert( Good(arr,num) );
        }

        inline LightArray(const LightArray &other) noexcept :
        SelfType(),
        cxx(other.cxx),
        count(other.count)
        {
        }

        inline virtual ~LightArray() noexcept
        {
            Coerce(cxx)=0;
            Coerce(count)=0;
        }

        inline virtual size_t size() const noexcept { return count; }

    private:
        Y_Disable_Assign(LightArray);
        MutableType * const cxx;
        const size_t        count;

        inline ConstType & getItemAt(const size_t i) const noexcept
        {
            return cxx[i];
        }
    };

}

#endif

