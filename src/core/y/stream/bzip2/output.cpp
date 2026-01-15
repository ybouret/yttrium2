
#if defined(_MSC_VER)
#pragma warning ( disable : 4464 )
#endif

#include "y/stream/bzip2/output.hpp"
#include "y/stream/libc/file/output.hpp"
#include "../../../../y/bzip2/bzlib.h"
#include "y/exception.hpp"
#include <cassert>

namespace Yttrium
{
    namespace BZip2
    {


        void * OutputFile:: setup(const int blockSize100k,
                                  const int workFactor)
        {
            Y_Giant_Lock();
            BZFILE * const h = BZ2_bzWriteOpen(& (err=BZ_OK), (**cfp).handle, blockSize100k, 0, workFactor);;
            if(BZ_OK != err)
                throw Specific::Exception(CallSign,"BZ2_bzWriteOpen: %s", ErrorText(err) );
            return h;
        }

        OutputFile:: ~OutputFile() noexcept
        {
            Y_Giant_Lock();
            BZ2_bzWriteClose(&err, (BZFILE *)bzf, 0, 0, 0);
        }


        void OutputFile:: write(const char c)
        {
            Y_Giant_Lock();
            BZ2_bzWrite(&(err=BZ_OK), (BZFILE *)bzf, (void*)&c,1);
            if(BZ_OK != err )
            {
                throw Specific::Exception(CallSign,"BZ2_bzWrite: %s", ErrorText(err) );
            }
        }

        void OutputFile:: flush()
        {
            Y_Giant_Lock();
            if( BZ_OK != (err = BZ2_bzflush( (BZFILE*)bzf) ))
                throw Specific::Exception(CallSign,"BZ2_bzflush: %s", ErrorText(err) );

        }
    }

}


