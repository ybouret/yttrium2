

//! \file

#ifndef Y_Libc_OutputFile_Included
#define Y_Libc_OutputFile_Included 1

#include "y/stream/output.hpp"
#include "y/stream/libc/types.hpp"

namespace Yttrium
{
    namespace Libc { class OutputFile; }

    class OutputFile : public OutputStream
    {
    public:
        class Code;
        explicit OutputFile(const char * const fileName, const bool append=false);
        explicit OutputFile(const StdOut_ &);
        explicit OutputFile(const StdErr_ &);
        virtual ~OutputFile() noexcept;

        virtual void write(const char C);
        virtual void flush();


    private:
        Y_Disable_Copy_And_Assign(OutputFile);
        Libc::OutputFile * const file;
    };

    class AppendFile : public OutputFile
    {
    public:
        explicit AppendFile(const char * const fileName);
        virtual ~AppendFile() noexcept;

    private:
        Y_Disable_Copy_And_Assign(AppendFile);
    };

}

#endif
