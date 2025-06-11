//! \file

#ifndef Y_Counted_Object_Included
#define Y_Counted_Object_Included 1

#include "y/object.hpp"
#include "y/counted.hpp"


namespace Yttrium
{
    class CountedObject : public Object, public Counted
    {
    public:
        explicit CountedObject() noexcept;
        virtual ~CountedObject() noexcept;
    private:
        Y_Disable_Copy_And_Assign(CountedObject);
    };
}

#endif

