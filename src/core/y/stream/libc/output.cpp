
#include "y/stream/libc/output.hpp"
#include "y/stream/libc/file/output.hpp"
#include "y/type/destroy.hpp"
#include "y/system/exception.hpp"
#include "y/ability/lockable.hpp"
#include "y/string.hpp"
#include <cstring>
#include "y/core/variadic.hpp"

#if defined(_MSC_VER)
#pragma warning ( disable : 4996 )
#endif

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
            const char * const how = append ? "ab" : "wb";
            FILE * const       fp  = fopen(fileName,how);
            if(!fp)
                throw Libc::Exception(errno,"fopen(%s,%s)", fileName,how);

            try { return new Libc::RegularOutputFile(fp); }
            catch(...) { (void)fclose(fp); throw; }
        }
    }


    OutputFile:: OutputFile(const char * const fileName, const bool append) :
    file( CreateFileFrom(fileName,append) ) 
    {

    }

    OutputFile:: OutputFile(const String &fileName, const bool append) :
    file( CreateFileFrom(fileName.c_str(),append) )
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

    void OutputFile:: frame(const void * const addr, const size_t size)
    {
        assert(0!=file);
        file->frame(addr,size);
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

    AppendFile:: AppendFile(const String &fileName) :
    OutputFile(fileName,true)
    {
    }

    AppendFile:: ~AppendFile() noexcept
    {
    }


    void OutputFile:: Echo(const String & filename, const char * const fmt,...)
    {
        static const char func[] = "OutputFile:Echo";
        AppendFile fp(filename);

        size_t length = 0;
        int    result = 0;
        {
            va_list ap;
            va_start(ap,fmt);
            result = Core::Variadic::Format(0,0,fmt, &ap);
            va_end(ap);
            if(result<0)
                throw Specific::Exception(func,"invalid format string");
            length = size_t( result );
        }

        String str(WithAtLeast,length,true); assert(str.size()==length);

        {
            va_list ap;
            va_start(ap,fmt);
            const int result2 = Core::Variadic::Format( str(),length+1,fmt, &ap);
            if(result2!=result)
                throw Specific::Exception(func,"corrupted variadic call");
            va_end(ap);
        }

        fp << str;

    }

}


