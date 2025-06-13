
//! \file

#ifndef Y_Libc_File_Input_Included
#define Y_Libc_File_Input_Included 1

#include "y/stream/libc/file.hpp"

namespace Yttrium
{
    namespace Libc
    {

        class InputFile : public File
        {
        public:
            explicit InputFile(const char * const fileName);
            virtual ~InputFile() noexcept;

        private:
            Y_Disable_Copy_And_Assign(InputFile);
        };

        class StdInFile : public File
        {
        public:
            explicit StdInFile();
            virtual ~StdInFile() noexcept;
            
        private:
            Y_Disable_Copy_And_Assign(StdInFile);
        };


    }

}

#endif
