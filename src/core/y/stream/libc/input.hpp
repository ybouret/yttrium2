
//! \file

#ifndef Y_Libc_Input_Included
#define Y_Libc_Input_Included 1

#include "y/stream/input.hpp"
#include "y/stream/libc/types.hpp"

namespace Yttrium
{
    namespace Libc { class InputFile; }

    class InputFile : public InputStream
    {
    public:
        class Code;
        explicit InputFile(const char * const fileName);
        explicit InputFile(const StdIn_ &);
        virtual ~InputFile() noexcept;

        virtual bool query(char &C);
        virtual void store(const char C);
        

    private:
        Y_Disable_Copy_And_Assign(InputFile);
        Libc::InputFile * const file;
    };

}

#endif
