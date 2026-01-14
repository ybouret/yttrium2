

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
        //! gzFile management
        //
        //
        //______________________________________________________________________
        class File
        {
        public:

            explicit File();
            virtual ~File() noexcept;

        protected:
            void * const bz2; //!< handle

        private:
            Y_Disable_Copy_And_Assign(File); //!< discarding
        };

    }
}

#endif // !Y_BZip2_File_Included

