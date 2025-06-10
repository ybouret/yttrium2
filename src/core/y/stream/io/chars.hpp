
//! \file

#ifndef Y_Stream_IO_Chars_Included
#define Y_Stream_IO_Chars_Included 1

#include "y/stream/io/char.hpp"
#include "y/concurrent/data/live-list.hpp"

namespace Yttrium
{
    namespace IO
    {

        class Chars : public Concurrent::LiveList<Char>
        {
        public:
            explicit Chars() noexcept;
            virtual ~Chars() noexcept;
            
        private:
            Y_Disable_Copy_And_Assign(Chars);
        };

    }
}


#endif


