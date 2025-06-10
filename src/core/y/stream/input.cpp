
#include "y/stream/input.hpp"
#include "y/stream/io/codec64.hpp"
#include "y/system/exception.hpp"
#include "y/decimal.hpp"

namespace Yttrium
{
    InputStream:: ~InputStream() noexcept
    {
    }

    InputStream:: InputStream() noexcept
    {
    }

    

    
    void InputStream:: decode64(uint64_t &qw)
    {
        static const char fn[] = "InputStream::decode64";

        static const size_t   MaxExtraBytes = IO::Codec64::MaxExtraBytes;
        //static const size_t   HeaderBits    = IO::Codec64::HeaderBits;
        static const size_t   HeaderRoll    = IO::Codec64::HeaderRoll;
        static const uint64_t HeaderMask    = IO::Codec64::HeaderMask;


        uint8_t header = 0;
        if(!query((char&)header) )throw Specific::Exception(fn,"missing header");
        const size_t  extraBytes = (header>>HeaderRoll);

        if(extraBytes>MaxExtraBytes)
            throw Specific::Exception(fn,"extraBytes=%s>%s", Decimal(extraBytes).c_str(), Decimal(MaxExtraBytes).c_str());

        qw = header & HeaderMask;
        unsigned shift = HeaderRoll;
        for(size_t i=1;i<=extraBytes;++i)
        {
            uint8_t extra = 0;
            if( !query( (char &)extra) ) throw Specific::Exception(fn,"missing extra char %s/%s", Decimal(i).c_str(), Decimal(extraBytes).c_str());
            qw |= (uint64_t(extra)<<shift);
            shift += 8;
        }

    }



}

