
#if defined(_MSC_VER)
#pragma warning ( disable : 4464 )
#endif

#include "y/stream/gzip/file/input.hpp"
#include "y/system/exception.hpp"
#include "y/ability/lockable.hpp"
#include "../../../../../y/zlib/zlib.h"
#include <cerrno>
#include <cassert>

namespace Yttrium
{
    namespace GZip
    {
        InputFile:: InputFile(const char * const fileName) :
        File(fileName,"r")
        {
        }

        InputFile:: ~InputFile() noexcept
        {

        }


        bool InputFile:: query1(char &c)
        {
            assert(gz);
            gzFile fp = (gzFile)gz;
            if( gzeof(fp)) return false;
            if( gzread(fp, &c, 1) < 0 )
                throw Specific::Exception("gzread","invalid stream");
            return true;
        }
    }

}


