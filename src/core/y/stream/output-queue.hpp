
//! \file

#ifndef Y_Output_Queue_Included
#define Y_Output_Queue_Included 1

#include "y/stream/output.hpp"
#include "y/stream/io/chars.hpp"

namespace Yttrium
{
    class OutputQueue : public OutputStream, public IO::Chars
    {
    public:
        explicit OutputQueue() noexcept;
        virtual ~OutputQueue() noexcept;

        Y_OSTREAM_PROTO(OutputQueue);

        virtual void write(const char);
        virtual void flush();




    private:
        Y_Disable_Copy_And_Assign(OutputQueue);
    };

}

#endif

