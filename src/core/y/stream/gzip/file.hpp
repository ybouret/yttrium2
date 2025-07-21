
//! \file
#ifndef Y_GZIP_File_Included
#define Y_GZIP_File_Included 1

#include "y/core/setup.hpp"
#include "y/type/copy-of.hpp"

namespace Yttrium
{
    namespace GZip
    {

        class File
        {
        public:
            explicit File(const char * const fileName, const char * const mode);
            virtual ~File() noexcept;

        protected:
            void * const gz;
            
        private:
            Y_Disable_Copy_And_Assign(File);
        };

    }
}

#endif

