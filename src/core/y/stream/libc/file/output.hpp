

//! \file

#ifndef Y_Libc_File_Output_Included
#define Y_Libc_File_Output_Included 1

#include "y/stream/libc/file.hpp"

namespace Yttrium
{
    namespace Libc
    {

        class OutputFile : public File
        {
        public:
            explicit OutputFile(const char * const fileName);
            virtual ~OutputFile() noexcept;

        private:
            Y_Disable_Copy_And_Assign(OutputFile);
        };

        class StdErrFile : public File
        {
        public:
            explicit StdErrFile();
            virtual ~StdErrFile() noexcept;

        private:
            Y_Disable_Copy_And_Assign(StdErrFile);
        };

        class StdOutFile : public File
        {
        public:
            explicit StdOutFile();
            virtual ~StdOutFile() noexcept;

        private:
            Y_Disable_Copy_And_Assign(StdOutFile);
        };

    }

}

#endif
