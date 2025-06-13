

//! \file

#ifndef Y_Libc_File_Output_Included
#define Y_Libc_File_Output_Included 1

#include "y/stream/libc/file/buffer.hpp"

namespace Yttrium
{
    namespace Libc
    {

        class OutputFile : public File
        {
        public:
            explicit OutputFile(FILE * const userFile, const bool closeOnQuit);
            virtual ~OutputFile() noexcept;

            void flush();
            void write(const char C);

        private:
            Y_Disable_Copy_And_Assign(OutputFile);
        };


        class RegularOutputFile : public OutputFile
        {
        public:
            explicit RegularOutputFile(FILE * const userFile);
            virtual ~RegularOutputFile() noexcept;

        private:
            Y_Disable_Copy_And_Assign(RegularOutputFile);
            FileBuffer buffer;
        };

        class StandardOutputFile : public OutputFile
        {
        public:
            explicit StandardOutputFile();
            virtual ~StandardOutputFile() noexcept;

        private:
            Y_Disable_Copy_And_Assign(StandardOutputFile);
        };

        class StandardErrorFile : public OutputFile
        {
        public:
            explicit StandardErrorFile();
            virtual ~StandardErrorFile() noexcept;

        private:
            Y_Disable_Copy_And_Assign(StandardErrorFile);
        };

    }

}

#endif
