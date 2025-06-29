
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


    static const char     fmt[]         = " for %s";


    void InputStream:: decode64(uint64_t &qw, const char * const varName)
    {
        static const char     fn[]          = "InputStream::decode64";
        static const size_t   MaxExtraBytes = IO::Codec64::MaxExtraBytes;
        static const size_t   HeaderRoll    = IO::Codec64::HeaderRoll;
        static const uint64_t HeaderMask    = IO::Codec64::HeaderMask;


        uint8_t header = 0;
        if(!query((char&)header) )
        {
            Specific::Exception excp(fn,"missing header");
            if(varName) excp.add(fmt,varName);
            throw excp;
        }
        const size_t  extraBytes = size_t(header>>HeaderRoll);

        if(extraBytes>MaxExtraBytes)
        {
            Specific::Exception excp(fn,"extraBytes=%s>%s", Decimal(extraBytes).c_str(), Decimal(MaxExtraBytes).c_str());
            if(varName) excp.add(fmt,varName);
            throw excp;
        }

        qw = header & HeaderMask;
        unsigned shift = HeaderRoll;
        for(size_t i=1;i<=extraBytes;++i)
        {
            uint8_t extra = 0;
            if( !query( (char &)extra) )
            {
                Specific::Exception excp(fn,"missing extra char %s/%s", Decimal(i).c_str(), Decimal(extraBytes).c_str());
                if(varName) excp.add(fmt,varName);
                throw excp;
            }
            qw |= (uint64_t(extra)<<shift);
            shift += 8;
        }

    }


    void InputStream:: throwOverflow(const char * const varName,
                                     const char * const varPart,
                                     const uint64_t     qw,
                                     const uint64_t     mx) const
    {
        Specific::Exception excp("InputStream::readVBR","read %s bigger than maximum %s", Decimal(qw).c_str(), Decimal(mx).c_str());
        if(varName) excp.add(fmt,varName);
        if(varPart) excp.add(".%s",varPart);
        throw excp;
    }


    size_t InputStream:: read(uint8_t &b)
    {
        return size_t( query( (char&)b )  ? 1 : 0 );
    }

    size_t InputStream:: read(uint16_t &w)
    {
        uint8_t b = 0;
        if(!read(b)) return 0;
        w = b;
        if(!read(b)) return 1;
        w |= uint16_t(b) << 8;
        return 2;
    }

    size_t InputStream:: read(uint32_t &w)
    {
        uint8_t b = 0;
        if(!read(b)) return 0;
        w = b;

        if(!read(b)) return 1;
        w |= uint32_t(b) << 8;

        if(!read(b)) return 2;
        w |= uint32_t(b) << 16;

        if(!read(b)) return 3;
        w |= uint32_t(b) << 24;

        return 4;
    }

    size_t InputStream:: read(uint64_t &w)
    {
        uint8_t b = 0;
        if(!read(b)) return 0;
        w = b;

        if(!read(b)) return 1;
        w |= uint64_t(b) << 8;

        if(!read(b)) return 2;
        w |= uint64_t(b) << 16;

        if(!read(b)) return 3;
        w |= uint64_t(b) << 24;

        if(!read(b)) return 4;
        w |= uint64_t(b) << 32;

        if(!read(b)) return 5;
        w |= uint64_t(b) << 40;

        if(!read(b)) return 6;
        w |= uint64_t(b) << 48;

        if(!read(b)) return 7;
        w |= uint64_t(b) << 56;

        return 8;
    }

}

#include "y/string.hpp"
namespace Yttrium
{

    bool InputStream:: gets(Core::String<char> &line)
    {
        line.free();
        char c;

        while(query(c))
        {
            switch(c)
            {
                case LF:
                    return true;

                case CR:
                    if(query(c))
                    {
                        if(LF!=c) store(c);
                    }
                    return true;

                default:
                    line << c;
                    continue;
            }
        }

        // EOF
        return line.size()>0;
    }

}

