

//! \file

#ifndef Y_Output_Stream_Included
#define Y_Output_Stream_Included 1

#include "y/stream/io/chars.hpp"

namespace Yttrium
{
    class OutputStream
    {
    protected:
        explicit OutputStream() noexcept;

    public:
        virtual ~OutputStream() noexcept;

    private:
        Y_Disable_Copy_And_Assign(OutputStream);
    };
}

#endif

