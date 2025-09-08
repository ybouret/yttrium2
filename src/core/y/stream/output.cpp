#include "y/stream/output.hpp"

#include "y/calculus/bits-for.hpp"
#include "y/calculus/alignment.hpp"
#include "y/stream/io/codec64.hpp"

namespace Yttrium
{
    OutputStream:: ~OutputStream() noexcept
    {
    }

    OutputStream:: OutputStream() noexcept
    {
    }


    size_t OutputStream:: encode64(uint64_t qw)
    {

        static const size_t   HeaderBits    = IO::Codec64::HeaderBits;
        static const size_t   HeaderRoll    = IO::Codec64::HeaderRoll;
        static const uint64_t HeaderMask    = IO::Codec64::HeaderMask;

        size_t       inputBits = Calculus::BitsFor::Count(qw);
        const size_t totalBits = inputBits + HeaderBits;
        const size_t totalSize = Alignment::On<8>::Ceil(totalBits) >> 3;
        const size_t extraSize = totalSize-1;
        assert(totalSize>=1);
        assert(totalSize<=1+IO::Codec64::MaxExtraBytes);


        // special case
        if(inputBits<=HeaderRoll)
        {
            assert(0==extraSize);
            write( (uint8_t(extraSize) << HeaderRoll) | uint8_t(qw) );
            return 1;
        }

        // fill bytes
        uint8_t byte[9];

        // write header
        byte[0]  = uint8_t(uint8_t(extraSize) << HeaderRoll);
        byte[0] |= uint8_t(qw & HeaderMask);

        // update qw
        inputBits -= HeaderRoll;
        qw       >>= HeaderRoll;
        assert( Calculus::BitsFor::Count(qw) == inputBits );
        assert( inputBits <= extraSize * 8);

        // remaining
        {
            uint8_t *p = byte;
            ++p;
            while(inputBits>=8)
            {
                *(p++) = uint8_t(qw);
                qw       >>= 8;
                inputBits -= 8;
            }
            assert( Calculus::BitsFor::Count(qw) < 8);
            *p = uint8_t(qw); // may be 0
        }

        for(size_t i=0;i<totalSize;++i)
            write( char(byte[i]) );

        return totalSize;
    }

    size_t OutputStream:: emit(const uint8_t &x)
    {
        write(char(x));
        return 1;
    }

    size_t OutputStream:: emit(const uint16_t &x)
    {
        uint16_t w = x;
        write(char(uint8_t(w))); w >>= 8;
        write(char(uint8_t(w)));
        return 2;
    }

    size_t OutputStream:: emit(const uint32_t &x)
    {
        uint32_t w = x;
        write(char(uint8_t(w))); w >>= 8;
        write(char(uint8_t(w))); w >>= 8;
        write(char(uint8_t(w))); w >>= 8;
        write(char(uint8_t(w)));
        return 4;
    }

    size_t OutputStream:: emit(const uint64_t &x)
    {
        uint64_t w = x;
        write(char(uint8_t(w))); w >>= 8;
        write(char(uint8_t(w))); w >>= 8;
        write(char(uint8_t(w))); w >>= 8;
        write(char(uint8_t(w))); w >>= 8;
        write(char(uint8_t(w))); w >>= 8;
        write(char(uint8_t(w))); w >>= 8;
        write(char(uint8_t(w))); w >>= 8;
        write(char(uint8_t(w)));
        return 8;
    }

    void OutputStream:: frame(const void * const entry, const size_t count)
    {
        const char * C = static_cast<const char *>( entry );
        for(size_t i=count;i>0;--i) write( *(C++) );
    }

}


#include "y/string.hpp"
#include "y/string/length.hpp"
#include "y/core/variadic.hpp"
#include "y/memory/buffer/out-of.hpp"
#include "y/exception.hpp"
#include "y/memory/allocator/pooled.hpp"
#include <cstdarg>

namespace Yttrium
{
    OutputStream & OutputStream:: operator<<( const char c ) { write(c); return *this; }

    OutputStream & OutputStream:: operator<<( const char * const text) {
        frame( text, StringLength(text) );
        return *this;
    }

    OutputStream & OutputStream::  operator<<( const Core::String<char> &s)
    {
        frame( s.c_str(), s.size() );
        return *this;
    }

    OutputStream &  OutputStream:: operator()(const char * const fmt,...)
    {
        static const char fn[] = "OutputStream(formatted)";
        assert(0!=fmt);
        size_t length = 0;
        int    result = 0;
        {
            va_list ap;
            va_start(ap,fmt);
            result = Core::Variadic::Format(0, 0, fmt, &ap);
            if(result<0) throw Specific::Exception(fn,"invalid format");
            va_end(ap);
            length = size_t(result);
        }

        const size_t required = length+1;
        Memory::BufferOutOf<Memory::Pooled> buffer( required );
        {
            va_list ap;
            va_start(ap,fmt);
            const int result2 = Core::Variadic::Format( (char *)buffer.rw(), required, fmt, &ap);
            if(result2!=result) throw Specific::Exception(fn,"corrupted format");
            va_end(ap);
        }
        
        frame(buffer.ro(),length);
        return *this;
    }
}
