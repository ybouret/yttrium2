
//! \file

#ifndef Y_Input_Stream_Included
#define Y_Input_Stream_Included 1

#include "y/stream/io/chars.hpp"

namespace Yttrium
{
    class InputStream
    {
    protected:
        explicit InputStream() noexcept;

    public:
        virtual ~InputStream() noexcept;
        
    private:
        Y_Disable_Copy_And_Assign(InputStream);
    };
}

#endif

