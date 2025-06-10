

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

        virtual void write(const char) = 0;
        virtual void flush()           = 0;

        size_t encode64(const uint64_t qw);

    private:
        Y_Disable_Copy_And_Assign(OutputStream);
    };
}

#endif

