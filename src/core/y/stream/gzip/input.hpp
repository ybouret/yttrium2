
//! \file
#ifndef Y_GZIP_Input_Included
#define Y_GZIP_Input_Included 1

#include "y/stream/input.hpp"
#include "y/stream/gzip/file.hpp"

namespace Yttrium
{
    namespace GZip
    {
        class Input : public File, public InputStream
        {
        public:

        private:
            Y_Disable_Copy_And_Assign(Input);
        };
    }

}

#endif

