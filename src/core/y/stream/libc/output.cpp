
#include "y/stream/libc/output.hpp"
#include "y/stream/libc/file/output.hpp"
#include "y/type/destroy.hpp"
#include "y/system/exception.hpp"
#include "y/ability/lockable.hpp"
#include <cstring>

namespace Yttrium
{
    namespace
    {
        static inline Libc::OutputFile * CreateFileFrom(const char * const fileName,
                                                        const bool         append)
        {
            assert(0!=fileName);

            if( 0==strcmp(fileName,Y_STDOUT) ) return new Libc::StandardOutputFile();
            if( 0==strcmp(fileName,Y_STDERR) ) return new Libc::StandardErrorFile();


            Y_Giant_Lock();
            FILE * const fp = fopen(fileName, append ? "ab" : "rb");
            if(!fp)
                throw Libc::Exception(errno,"fopen(%s)", fileName);

            try { return new Libc::RegularOutputFile(fp); }
            catch(...) { fclose(fp); throw; }
        }
    }


    OutputFile:: OutputFile(const char * const fileName, const bool append) :
    file( CreateFileFrom(fileName,append) ) 
    {

    }

    OutputFile:: OutputFile(const StdOut_ &) :
    file(  new Libc::StandardOutputFile() )
    {
    }

    OutputFile:: OutputFile(const StdErr_ &) :
    file(  new Libc::StandardErrorFile() )
    {
    }



    OutputFile:: ~OutputFile() noexcept
    {
        assert(0!=file);
        Destroy( Coerce(file) );
    }

    void OutputFile:: write(const char C)
    {
        assert(0!=file);
        file->write(C);
    }

    void OutputFile:: flush()
    {
        assert(0!=file);
        file->flush();
    }

    AppendFile:: AppendFile(const char * const fileName) :
    OutputFile(fileName,true)
    {
    }

    AppendFile:: ~AppendFile() noexcept
    {
    }




}


