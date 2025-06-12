
#include "y/container/dynamic.hpp"
#include "y/type/ints.hpp"
#include "y/core/utils.hpp"
#include "y/system/exception.hpp"

namespace Yttrium
{

    DynamicContainer:: ~DynamicContainer() noexcept
    {
    }

    DynamicContainer:: DynamicContainer() noexcept
    {
    }


    
    size_t DynamicContainer:: NextIncrease(const size_t currentCapacity)
    {
        static const size_t MaxCapacity = IntegerFor<size_t>::Maximum;
        const size_t        increase    = MaxOf<size_t>(currentCapacity >> 1,8);
        if(MaxCapacity-increase<currentCapacity)
            throw Specific::Exception("DynamicContainer::NextIncrease","capacity overflow");
        return  increase;
    }

    size_t DynamicContainer:: NextCapacity(const size_t currentCapacity)
    {
        return currentCapacity+NextIncrease(currentCapacity);
    }
}


