//! \file

#ifndef Y_Libc_File_Included
#define Y_Libc_File_Included 1

#include "y/object.hpp"
#include <cstdio>

namespace Yttrium
{
    namespace Libc
    {

        //______________________________________________________________________
        //
        //
        //
        //! low-level FILE wrapper
        //
        //
        //______________________________________________________________________
        class File
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup
            /**
             \param userFile a valid FILE
             \param closeOnQuit will call fclose iff true
             */
            explicit File(FILE * const userFile,
                          const bool   closeOnQuit) noexcept;

            //! cleanup
            virtual ~File() noexcept;

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            FILE * const handle;    //!< valid FILE
            const bool   mustClose; //!< closing when destructing

        private:
            Y_Disable_Copy_And_Assign(File); //!< discarding
        };
    }
}

#endif

