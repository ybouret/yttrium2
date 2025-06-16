
//! \file

#ifndef Y_Stream_Queue_Included
#define Y_Stream_Queue_Included 1

#include "y/stream/output.hpp"
#include "y/stream/input.hpp"

#include "y/stream/io/chars.hpp"

namespace Yttrium
{
    //__________________________________________________________________________
    //
    //
    //
    //! Helper for I/O
    //
    //
    //__________________________________________________________________________
    class StreamQueue : public InputStream, public OutputStream, public IO::Chars
    {
    public:
        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
        explicit StreamQueue() noexcept; //!< setup
        virtual ~StreamQueue() noexcept; //!< cleanup
        Y_OSTREAM_PROTO(StreamQueue);    //!< display

        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________
        virtual void       write(const char);
        virtual void       flush();
        virtual void       frame(const void * const, const size_t);


        virtual bool       query(char &);
        virtual void       store(const char);

    private:
        Y_Disable_Copy_And_Assign(StreamQueue); //!< discard
    };

}

#endif

