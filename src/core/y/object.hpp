//! \file

#ifndef Y_Object_Included
#define Y_Object_Included 1

#include "y/core/setup.hpp"

namespace Yttrium
{

    class Object
    {
    public:
        class Factory;
        
        explicit Object() noexcept;
        virtual ~Object() noexcept;

    private:
        Y_Disable_Copy_And_Assign(Object);
    };

}

#endif
