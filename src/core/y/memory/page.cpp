
#include "y/memory/page.hpp"
#include <cassert>
#include <cstring>

namespace Yttrium
{
    namespace Memory
    {
        void * Page:: Addr(Page *const page, const size_t bytes) noexcept
        {
            assert(0!=page);
            assert(bytes>=sizeof(Page));
            return memset(page,0,bytes);
        }

        Page * Page:: Cast(void * const addr) noexcept
        {
            assert(0!=addr);
            return static_cast<Page *>(memset(addr,0,sizeof(Page)));
        }
    }

}
