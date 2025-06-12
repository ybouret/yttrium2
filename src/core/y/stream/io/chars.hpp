
//! \file

#ifndef Y_Stream_IO_Chars_Included
#define Y_Stream_IO_Chars_Included 1

#include "y/stream/io/char.hpp"
#include "y/concurrent/data/live-list.hpp"

namespace Yttrium
{
    namespace IO
    {

        typedef LiveList<IO::Char> Chars;

    }
}


#endif


