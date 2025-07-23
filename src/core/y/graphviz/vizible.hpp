//! \file

#ifndef Y_Vizible_Included
#define Y_Vizible_Included 1

#include "y/stream/output.hpp"

namespace Yttrium
{
    class Vizible
    {
    public:
        explicit Vizible() noexcept;
        virtual ~Vizible() noexcept;

        OutputStream & name(OutputStream &) const;
        OutputStream & to(const Vizible * const, OutputStream &fp) const;

        static OutputStream & Endl(OutputStream &);


    private:
        Y_Disable_Copy_And_Assign(Vizible);

    };
}

#endif

