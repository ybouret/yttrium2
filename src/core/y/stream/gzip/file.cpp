
#include "y/stream/gzip/file.hpp"
#include <cassert>
#include "y/system/exception.hpp"
#include "y/ability/lockable.hpp"
#include "y/zlib/zlib.h"
#include <cerrno>

namespace Yttrium
{
    namespace GZip
    {
        File:: ~File() noexcept
        {
            assert(0!=gz);
            (void) gzclose( (gzFile)gz );
        }

        File:: File(const char * const fileName, const char * const mode) :
        gz(0)
        {
            assert(0!=fileName);
            assert(0!=mode);
            Y_Giant_Lock();
            Coerce(gz) = gzopen(fileName,mode);
            if(!gz) throw Libc::Exception(errno,"gzopen(%s,%s)", fileName, mode);
        }
    }
}
