

//! \file
#ifndef Y_BZip2_File_Included
#define Y_BZip2_File_Included 1

#include "y/core/setup.hpp"

namespace Yttrium
{
    namespace BZip2
    {

        //______________________________________________________________________
        //
        //
        //
        //! BZFILE
        //
        //
        //______________________________________________________________________
        class File
        {
        public:
            static const char * const CallSign;
            static const char * ErrorText(const int err) noexcept;
            
            virtual ~File() noexcept;

        protected:
            explicit File() noexcept;

        private:
            Y_Disable_Copy_And_Assign(File); //!< discarding
        };

    }
}

#endif // !Y_BZip2_File_Included

