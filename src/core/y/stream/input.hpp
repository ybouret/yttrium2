
//! \file

#ifndef Y_Input_Stream_Included
#define Y_Input_Stream_Included 1

#include "y/stream/io/chars.hpp"

namespace Yttrium
{
    class InputStream
    {
    protected:
        explicit InputStream() noexcept;

    public:
        virtual ~InputStream() noexcept;

        virtual bool query(char &C) = 0;

        void decode64(uint64_t &qw);

        template <typename T> inline
        size_t readCBR(T &value)
        {
            union
            {
                typename UnsignedIntFor<T>::Result::Type y;
                T x;
            } alias = { 0 };
            const size_t res = read(alias.y);
            value = alias.x;
            return res;
        }

    private:
        Y_Disable_Copy_And_Assign(InputStream);
        size_t read(uint8_t  &x);
        size_t read(uint16_t &w);
        size_t read(uint32_t &w);
        size_t read(uint64_t &w);

    };
}

#endif

