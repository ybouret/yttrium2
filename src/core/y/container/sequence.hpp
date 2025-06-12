
//! \file

#ifndef Y_Sequence_Included
#define Y_Sequence_Included 1

#include "y/container/dynamic.hpp"

namespace Yttrium
{

    template <typename T>
    class Sequence : public DynamicContainer
    {
    protected:
        inline explicit Sequence() noexcept : DynamicContainer() {}

    public:
        inline virtual ~Sequence() noexcept {}


    private:
        Y_Disable_Copy_And_Assign(Sequence);
    };

}

#endif
