

#if defined(_MSC_VER)
#pragma warning ( disable : 4464 )
#endif

#include "y/stream/bzip2/file.hpp"
#include "y/system/exception.hpp"
#include "y/ability/lockable.hpp"
#include "../../../../y/bzip2/bzlib.h"
#include <cerrno>
#include <cassert>

namespace Yttrium
{
    namespace BZip2
    {

        

        File:: ~File() noexcept
        {
            
        }
    }
}
