
//! \file

#ifndef Y_Libc_Input_Included
#define Y_Libc_Input_Included 1

#include "y/stream/input.hpp"

namespace Yttrium
{

    class InputFile
    {
    public:
        explicit InputFile(const char * const fileName);
        explicit InputFile();
        virtual ~InputFile() noexcept;

    private:
        Y_Disable_Copy_And_Assign(InputFile);
    };

}

#endif
