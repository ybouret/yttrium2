
#include "y/stream/libc/file/input.hpp"
#include "y/ability/lockable.hpp"
#include "y/system/exception.hpp"
#include <cerrno>

namespace Yttrium
{
    namespace Libc
    {
        InputFile:: ~InputFile() noexcept
        {
        }


        InputFile:: InputFile(FILE * const userHandle, const bool closeOnQuit) :
        File(userHandle,closeOnQuit),
        Q()
        {
        }


        bool InputFile:: query(char &C)
        {
            if (Q.size())
            {
                C = char(Q.pullHead());
                return true;
            }
            Y_Giant_Lock();
            if( 1 != fread(&C,1, 1,handle) )
            {
                if( ferror(handle) ) throw Libc::Exception(errno,"InputFile::query");
                return false;
            }
            return true;
        }

        void InputFile:: store(const char C)
        {
            Q >> uint8_t(C);
        }


    }

}

namespace Yttrium
{
    namespace Libc
    {
        RegularInputFile:: ~RegularInputFile() noexcept
        {
        }

        RegularInputFile:: RegularInputFile(FILE * const fp) :
        FileBuffer(),
        InputFile(fp,true)
        {
            bufferize(*this);
        }
    }

}


namespace Yttrium
{
    namespace Libc
    {
        static FILE * GetStdIn()
        {
            if(!stdin) throw Specific::Exception("Libc::StdIn","stdin was closed");
            return stdin;
        }

        StandarInputFile:: StandarInputFile() :
        InputFile(GetStdIn(),false)
        {

        }

        StandarInputFile:: ~StandarInputFile() noexcept
        {
        }
        
    }
}

