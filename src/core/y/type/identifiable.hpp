
//! \file

#ifndef Y_Type_Identifiable_Included
#define Y_Type_Identifiable_Included 1

#include "y/core/setup.hpp"

namespace Yttrium
{

    class Identifiable
    {
    protected:
        explicit Identifiable() noexcept;
    public:
        virtual ~Identifiable() noexcept;

        virtual const char * callSign() const noexcept = 0;

    private:
        Y_Disable_Copy_And_Assign(Identifiable);
    };

}

#endif
