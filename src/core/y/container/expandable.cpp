
#include "y/container/expandable.hpp"
#include "y/type/ints.hpp"
#include "y/core/utils.hpp"
#include "y/system/exception.hpp"

namespace Yttrium
{

    Expandable:: ~Expandable() noexcept
    {
    }

    Expandable:: Expandable() noexcept : Gradual()
    {
    }

    size_t Expandable:: NextIncrease(const size_t currentCapacity)
    {
        static const size_t MaxCapacity = IntegerFor<size_t>::Maximum;
        const size_t        increase    = MaxOf<size_t>(currentCapacity >> 1,8);
        if(MaxCapacity-increase<currentCapacity)
            throw Specific::Exception("Expandable::NextIncrease","capacity overflow");
        return  increase;
    }

    size_t Expandable:: NextCapacity(const size_t currentCapacity)
    {
        return currentCapacity+NextIncrease(currentCapacity);
    }


    void Expandable:: ensure(const size_t minCapacity)
    {
        if(minCapacity>capacity()) reserve(minCapacity-capacity());
    }
}

