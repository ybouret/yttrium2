#include "y/stream/libc/input.hpp"
#include "y/stream/libc/file/input.hpp"
#include "y/stream/io/chars.hpp"
#include "y/type/destroy.hpp"
#include "y/system/exception.hpp"
#include "y/ability/lockable.hpp"
#include "y/string.hpp"
#include <cstring>

#if defined(_MSC_VER)
#pragma warning ( disable : 4996 )
#endif

namespace Yttrium
{
    namespace
    {
        static inline Libc::InputFile * CreateFileFrom(const char * const fileName)
        {
            assert(0!=fileName);

            if( 0==strcmp(fileName,Y_STDIN) )
                return new Libc::StandardInputFile();

            Y_Giant_Lock();
            FILE * const fp = fopen(fileName, "rb");
            if(!fp)
                throw Libc::Exception(errno,"fopen(%s)", fileName);

            try { return new Libc::RegularInputFile(fp); }
            catch(...) { fclose(fp); throw; }
        }
    }

    InputFile:: InputFile(const char * const fileName) :
    file( CreateFileFrom(fileName) )
    {

    }

    InputFile:: InputFile(const String &fileName ):
    file( CreateFileFrom(fileName.c_str()) )
    {

    }


    InputFile:: InputFile(const StdIn_ &) : file( new Libc::StandardInputFile() )
    {
        
    }


    InputFile:: ~InputFile() noexcept
    {
        assert(0!=file);
        Destroy( Coerce(file) );
    }

    bool InputFile:: query(char &C)
    {
        assert(0!=file);
        return file->query(C);
    }

    void InputFile:: store(const char C)
    {
        file->store(C);
    }

    Libc::InputFile & InputFile:: operator*() noexcept
    {
        return *file;
    }

}


