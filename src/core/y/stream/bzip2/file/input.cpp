#if defined(_MSC_VER)
#pragma warning ( disable : 4464 )
#endif

#include "y/stream/bzip2/file/input.hpp"
#include "y/stream/libc/file/input.hpp"
#include "../../../../../y/bzip2/bzlib.h"
#include "y/exception.hpp"
#include <cassert>

namespace Yttrium
{
    namespace BZip2
    {
        

        void * InputFile:: setup(const bool small)
        {
            BZFILE * const h = BZ2_bzReadOpen(& (err=BZ_OK), (**cfp).handle, 0, small ? 1 : 0, 0, 0);
            if(BZ_OK != err)
                throw Specific::Exception(CallSign,"BZ2_bzReadOpen: %s", ErrorText(err) );
            return h;
        }

        InputFile:: ~InputFile() noexcept
        {
            BZ2_bzReadClose(&err, (BZFILE *)bzf );
        }

        bool InputFile:: query(char &C)
        {
            Libc::InputFile &f = **cfp;
            IO::Chars       &Q = f.Q;

            if (Q.size())
            {
                C = char(Q.pullHead());
                return true;
            }
            else
            {
                Y_Giant_Lock();
                const int len = BZ2_bzRead( &err, (BZFILE*)bzf, &C, 1);
                if(1!=len)
                {
                    switch(err)
                    {
                        case BZ_OK:
                        case BZ_STREAM_END:
                            break;
                        default:
                            if( f.atEOF() ) return false;
                            throw Specific::Exception(CallSign,"BZ2_bzRead: %s", ErrorText(err));
                    }
                    return false;
                }
                return true;
            }
        }

        void InputFile:: store(const char C)
        {
            (**cfp).Q >> uint8_t(C);
        }

    }

}


