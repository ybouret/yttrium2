
//! \file

#ifndef Y_Modifiable_Included
#define Y_Modifiable_Included 1

#include "y/core/setup.hpp"
#include "y/string/fwd.hpp"

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //! one way flag
    //
    //
    //__________________________________________________________________________
    class Freezable
    {
    public:
        explicit Freezable() noexcept;
        virtual ~Freezable() noexcept;

        void freeze() noexcept;
        bool frozen() const noexcept;

        void checkpoint(const char * const)         const;
        void checkpoint(const Core::String<char> &) const;

    private:
        Y_Disable_Copy_And_Assign(Freezable);
        bool flag;
    };

}
#endif

