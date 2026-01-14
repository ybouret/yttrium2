


//! \file
#ifndef Y_BZip2_InputFile_Included
#define Y_BZip2_InputFile_Included 1

#include "y/stream/bzip2/file.hpp"
#include "y/stream/libc/input.hpp"
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
        class InputFile : public File
        {
        public:
            template <typename PARAM>
            explicit InputFile(const PARAM & param,
                               const bool small = false) :
            cfp( new Yttrium::InputFile(param) ),
            err(0),
            bzf( setup(small) )
            {
            }

            virtual ~InputFile() noexcept;


        private:
            Y_Disable_Copy_And_Assign(InputFile); //!< discarding
            ArcPtr<Yttrium::InputFile> cfp;
            int                        err;
            void * const               bzf;

            void * setup(const bool small);
        };

    }
}

#endif // !Y_BZip2_InputFile_Included

