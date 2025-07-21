
#ifndef Y_GZIP_InputFile_Included
#define Y_GZIP_InputFile_Included 1

#include "y/stream/gzip/file.hpp"

namespace Yttrium
{
    namespace GZip
    {

        class InputFile : public File
        {
        public:
            explicit InputFile(const char * const fileName);
            virtual ~InputFile() noexcept;

            bool query1(char &c);
            

        private:
            Y_Disable_Copy_And_Assign(InputFile);
        };

    }
}

#endif
