

//! \file

#ifndef Y_Output_Stream_Included
#define Y_Output_Stream_Included 1

#include "y/stream/io/chars.hpp"

namespace Yttrium
{
    class OutputStream
    {
    protected:
        explicit OutputStream() noexcept;

    public:
        virtual ~OutputStream() noexcept;

        virtual void write(const char) = 0;
        virtual void flush()           = 0;

        size_t encode64(const uint64_t qw);

        template <typename T>
        size_t emitVBR(const T &value)
        {
            return encode64( value );
        }

    private:
        Y_Disable_Copy_And_Assign(OutputStream);
        size_t emit(const uint8_t  &);
        size_t emit(const uint16_t &);
        size_t emit(const uint32_t &);
        size_t emit(const uint64_t &);

    };
}

#endif

