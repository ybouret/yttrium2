#include "y/stream/libc/file/output.hpp"
#include "y/ability/lockable.hpp"
#include "y/system/exception.hpp"
#include "y/format/decimal.hpp"
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
            if( 0 != fflush(handle) ) throw Libc::Exception(errno,"OutputFile::flush");
        }


        void OutputFile:: write(const char C)
        {
            Y_Giant_Lock();
            if( 1 != fwrite(&C, 1, 1, handle) ) throw Libc::Exception(errno,"OutputFile::write(0x%02x)", uint8_t(C) );
        }

        void OutputFile:: frame(const void * const addr, const size_t size)
        {
            Y_Giant_Lock();
            if( size != fwrite(addr, 1, size, handle) ) throw Libc::Exception(errno,"OutputFile::frame(%s)", Decimal(size).c_str());
        }

    }

}

namespace Yttrium
{
    namespace Libc
    {
        RegularOutputFile:: RegularOutputFile(FILE * const userFile) :
        FileBuffer(),
        OutputFile(userFile,true)
        {
            bufferize(*this);
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
