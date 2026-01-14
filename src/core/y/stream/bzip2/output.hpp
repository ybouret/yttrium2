



//! \file
#ifndef Y_BZip2_OutputFile_Included
#define Y_BZip2_OutputFile_Included 1

#include "y/stream/bzip2/file.hpp"
#include "y/stream/libc/output.hpp"
#include "y/pointer/arc.hpp"

namespace Yttrium
{
    namespace BZip2
    {

        //______________________________________________________________________
        //
        //
        //
        //!
        //
        //
        //______________________________________________________________________
        class OutputFile : public File, public OutputStream
        {
        public:
            template <typename PARAM>
            explicit OutputFile(const PARAM & param,
                                const int blockSize100k = 9,
                                const int workFactor    = 250) :
            cfp( new Yttrium::OutputFile(param) ),
            err(0),
            bzf( setup(blockSize100k,workFactor) )
            {
            }

            virtual ~OutputFile() noexcept;

            virtual void write(const char);
            virtual void flush();


        private:
            Y_Disable_Copy_And_Assign(OutputFile); //!< discarding
            ArcPtr<Yttrium::OutputFile> cfp;
            int                         err;
            void * const                bzf;

            void * setup(const int blockSize100k,
                         const int workFactor);
        };

    }
}

#endif // !Y_BZip2_OutputFile_Included

