

#include "y/stream/libc/file/copy.hpp"
#include "y/system/exception.hpp"
#include "y/stream/libc/file/input.hpp"
#include "y/stream/libc/file/output.hpp"
#include "y/hashing/function.hpp"

namespace Yttrium
{
    namespace Libc
    {
        void FileCopy:: Run(OutputFile &target, InputFile &source, Hashing::Function * const H)
        {
            static const char fn[] = "FileCopy";

            char buff[BUFSIZ];
            assert(target.handle);
            assert(source.handle);
            Y_Giant_Lock();

            FILE * const in   = source.handle;
            FILE * const out  = target.handle;
            bool         done = false;
            
        READ:
            const size_t nr   = fread(buff,1,BUFSIZ,in);
            if(nr<BUFSIZ)
            {
                if( feof(in) ) {
                    done = true;
                    goto WRITE;
                }

                if( ferror(in) )
                {
                    throw Libc::Exception(errno,fn);
                }

                throw Specific::Exception(fn,"unexpected read failure");
            }

        WRITE:
            const size_t nw = fwrite(buff,1,nr,out);
            if(H) H->run(buff,nr);
            if(nw<nr) throw Libc::Exception(errno,fn);
            if(done) return;
            goto READ;
        }

        void FileCopy:: Run(Yttrium::OutputFile &output, Yttrium::InputFile &input, Hashing::Function * const H)
        {
            Run(*output,*input,H);
        }
    }
}
