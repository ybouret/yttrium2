//! \file

#ifndef Y_Libc_File_Included
#define Y_Libc_File_Included 1

#include "y/core/setup.hpp"
#include <cstdio>

namespace Yttrium
{
    namespace Libc
    {

        class File
        {
        public:
            explicit File(FILE * const userFile,
                          const bool   closeOnQuit) noexcept;
            virtual ~File() noexcept;

            
            FILE * const handle;
            const bool   mustClose;

        private:
            Y_Disable_Copy_And_Assign(File);
        };
    }
}

#endif

