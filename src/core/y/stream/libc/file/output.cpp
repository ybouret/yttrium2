#include "y/stream/libc/file/output.hpp"
#include "y/ability/lockable.hpp"
#include "y/system/exception.hpp"
#include <cerrno>

namespace Yttrium
{
    namespace Libc
    {
        OutputFile:: ~OutputFile() noexcept
        {
        }



        OutputFile:: OutputFile( FILE * const userFile, const bool closeOnQuit) :
        File(userFile, closeOnQuit)
        {
        }

        void OutputFile:: flush()
        {
            Y_Giant_Lock();
            if( !fflush(handle) ) throw Libc::Exception(errno,"OutputFile::flush");
        }


        void OutputFile:: write(const char C)
        {
            Y_Giant_Lock();
            if( 1 != fwrite(&C, 1, 1, handle) ) throw Libc::Exception(errno,"OutputFile::write");
        }

    }

}

namespace Yttrium
{
    namespace Libc
    {
        RegularOutputFile:: RegularOutputFile(FILE * const userFile) :
        OutputFile(userFile,true), buffer()
        {
            buffer(*this);
        }

        RegularOutputFile:: ~RegularOutputFile() noexcept
        {
            
        }
    }
}


namespace Yttrium
{
    namespace Libc
    {
        static inline
        FILE * GetStdOut()
        {
            if(!stdout) throw Specific::Exception("Libc::StdOut","stdout was closed");
            return stdout;
        }

        StandardOutputFile:: StandardOutputFile() :
        OutputFile( GetStdOut(),false)
        {
        }

        StandardOutputFile:: ~StandardOutputFile() noexcept
        {

        }
    }
}


namespace Yttrium
{
    namespace Libc
    {
        static inline
        FILE * GetStdErr()
        {
            if(!stderr) throw Specific::Exception("Libc::StdErr","stderr was closed");
            return stderr;
        }

        StandardErrorFile:: StandardErrorFile() :
        OutputFile(GetStdErr(),false)
        {
        }

        StandardErrorFile:: ~StandardErrorFile() noexcept
        {

        }
    }
}
