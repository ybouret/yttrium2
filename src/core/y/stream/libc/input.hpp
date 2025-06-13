
//! \file

#ifndef Y_Libc_Input_Included
#define Y_Libc_Input_Included 1

#include "y/stream/input.hpp"
#include "y/stream/libc/types.hpp"

namespace Yttrium
{
    namespace Libc { class File; }

    class InputFile : public InputStream
    {
    public:
        class Code;
        explicit InputFile(const char * const fileName);
        explicit InputFile(const StdIn_ &);
        virtual ~InputFile() noexcept;

    private:
        Y_Disable_Copy_And_Assign(InputFile);
        Libc::File * const file;
    };

}

#endif
