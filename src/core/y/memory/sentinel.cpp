
#include "y/memory/sentinel.hpp"
#include "y/check/usual.hpp"
#include "y/check/crc32.hpp"
#include "y/system/error.hpp"
#include "y/format/decimal.hpp"
#include <cerrno>

namespace Yttrium
{
    namespace Memory
    {

        uint32_t Sentinel:: Setup(const void *const addr, const size_t size) noexcept
        {
            assert( Good(addr,size) );
            return CRC32::Of(addr,size);
        }

        Sentinel:: Sentinel(const void * const userBlock, const size_t userBytes) noexcept :
        addr(userBlock),
        size(userBytes),
        crc( Setup(addr,size) )
        {

        }

        Sentinel:: ~Sentinel() noexcept
        {
            if( Setup(addr,size) != crc )
                Libc::Error::Critical(EINVAL, "Memory::Sentinel @%p+%s",addr,Decimal(size).c_str());
        }

    }

}

