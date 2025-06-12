
//! \file

#ifndef Y_Stream_Queue_Included
#define Y_Stream_Queue_Included 1

#include "y/stream/output.hpp"
#include "y/stream/input.hpp"

#include "y/stream/io/chars.hpp"

namespace Yttrium
{
    class StreamQueue : public InputStream, public OutputStream //, public IO::Chars
    {
    public:
        explicit StreamQueue() noexcept;
        virtual ~StreamQueue() noexcept;

        Y_OSTREAM_PROTO(StreamQueue);

        virtual void       write(const char);
        virtual void       flush();
        virtual bool       query(char &C);
        virtual void       store(const char);

    private:
        Y_Disable_Copy_And_Assign(StreamQueue);
    };

}

#endif

