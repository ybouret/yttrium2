
#include "y/vfs/vfs.hpp"

namespace Yttrium
{

    VFS::Scanner:: Scanner(VFS &_, const String &__)  :
    vfs(_), dir(__)
    {
        String tmp = MakeDirName(dir);
        Coerce(dir).swapFor(tmp);
    }

    VFS::Scanner:: ~Scanner() noexcept
    {
    }

    
    
}
