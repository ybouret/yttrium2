
//! \file

#ifndef Y_Libc_File_Input_Included
#define Y_Libc_File_Input_Included 1

#include "y/stream/libc/file.hpp"
#include "y/stream/io/chars.hpp"

namespace Yttrium
{
    namespace Libc
    {


        class InputFile : public File
        {
        public:
            explicit InputFile(FILE * const userFile, const bool closeOnQuit);
            virtual ~InputFile() noexcept;

        private:
            Y_Disable_Copy_And_Assign(InputFile);
            IO::Chars Q;
        };

        class RegularInputFile : public InputFile
        {
        public:
            explicit RegularInputFile(FILE * const fp);
            virtual ~RegularInputFile() noexcept;
            
        private:
            Y_Disable_Copy_And_Assign(RegularInputFile);
        };


        class StandarInputFile : public InputFile
        {
        public:
            explicit StandarInputFile();
            virtual ~StandarInputFile() noexcept;

        private:
            Y_Disable_Copy_And_Assign(StandarInputFile);
        };

    }

}

#endif
