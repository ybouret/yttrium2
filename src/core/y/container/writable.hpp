

//! \file

#ifndef Y_Container_Writable_Included
#define Y_Container_Writable_Included 1

#include "y/container/readable.hpp"

namespace Yttrium
{

    template <typename T> class Writable : public Readable<T>
    {
    public:
        Y_ARGS_EXPOSE(T,Type);
        using Readable<T>::size;
        using Readable<T>::getItemAt;

    protected:
        inline explicit Writable() noexcept : Readable<T>() {}

    public:
        inline virtual ~Writable() noexcept {}

        inline Type & operator[](const size_t indx) noexcept
        {
            assert(indx>0); assert(indx<=size());
            return Coerce(getItemAt(indx));
        }

    private:
        Y_Disable_Copy_And_Assign(Writable);
    };

}

#endif

