
//! \file
#ifndef Y_GZIP_Input_Included
#define Y_GZIP_Input_Included 1

#include "y/stream/input.hpp"
#include "y/stream/gzip/file/input.hpp"
#include "y/stream/io/chars.hpp"

namespace Yttrium
{
    namespace GZip
    {
        class Input : public InputFile, public InputStream
        {
        public:
            explicit Input(const char * const);
            virtual ~Input() noexcept;

            virtual bool query(char &);
            virtual void store(const char);


        private:
            Y_Disable_Copy_And_Assign(Input);
            IO::Chars buffer;
        };
    }

}

#endif

