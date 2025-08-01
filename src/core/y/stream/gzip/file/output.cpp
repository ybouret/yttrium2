
#if defined(_MSC_VER)
#pragma warning ( disable : 4464 )
#endif

#include "y/stream/gzip/file/output.hpp"
#include "y/system/exception.hpp"
#include "y/ability/lockable.hpp"
#include "../../../../../y/zlib/zlib.h"
#include <cerrno>
#include <cassert>
#include <cstring>
namespace Yttrium
{
    namespace GZip
    {
        OutputMode:: OutputMode(const unsigned level,
                                const bool     append) :
        mode()
        {
            memset(mode,0,sizeof(mode));
            mode[0] = append ? 'a' : 'w';
            if(level>9) throw Specific::Exception("gzFile","level=%u is too big",level);
            mode[1] = char('0' + level);
        }

        OutputMode:: ~OutputMode() noexcept
        {
            memset(mode,0,sizeof(mode));
        }


        OutputFile:: ~OutputFile() noexcept
        {

        }

        OutputFile:: OutputFile(const char * const fileName,
                                const unsigned     level,
                                const bool         append) :
        OutputMode(level,append),
        File(fileName,mode)
        {

        }

        void OutputFile:: flush_()
        {
            const int err = gzflush((gzFile)gz, Z_FINISH);
            if( err != Z_OK )
                throw Specific::Exception("gzFlush","error %d",err);
        }


        void OutputFile:: write_(const char c)
        {
            if(1!=gzwrite((gzFile)gz, &c, 1))
            {
                throw Specific::Exception("gzWrite","I/O error");
            }
        }

    }

}


