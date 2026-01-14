

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
            static const char * const CallSign; //!< "BZip2"
            static const char * ErrorText(const int) noexcept; //!< \return named error vode

            virtual ~File() noexcept; //!< cleanup

        protected:
            explicit File() noexcept; //!< setup

        private:
            Y_Disable_Copy_And_Assign(File); //!< discarding
        };

    }
}

#endif // !Y_BZip2_File_Included

