
//! \file

#ifndef Y_Sequence_Included
#define Y_Sequence_Included 1

#include "y/container/dynamic.hpp"

namespace Yttrium
{

    template <typename T, typename CONTAINER>
    class Sequence : public CONTAINER
    {
    protected:
        inline explicit Sequence() noexcept : CONTAINER() {}

    public:
        inline virtual ~Sequence() noexcept {}


    private:
        Y_Disable_Copy_And_Assign(Sequence);
    };

}

#endif
