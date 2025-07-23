//! \file

#ifndef Y_Vizible_Included
#define Y_Vizible_Included 1

#include "y/string/fwd.hpp"
#include "y/core/setup.hpp"

namespace Yttrium
{
    class OutputStream;

    class Vizible
    {
    public:
        static const char *Char[256];

        explicit Vizible() noexcept;
        virtual ~Vizible() noexcept;

        OutputStream & name(OutputStream &) const;
        OutputStream & to(const Vizible * const, OutputStream &fp) const;

        static OutputStream & Label(OutputStream &, const Core::String<char> &);
        static OutputStream & Label(OutputStream &, const char * const);
        static OutputStream & Endl(OutputStream &);


    private:
        Y_Disable_Copy_And_Assign(Vizible);

    };
}

#endif

