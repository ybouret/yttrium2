
//! \file
#ifndef Y_GZIP_File_Included
#define Y_GZIP_File_Included 1

#include "y/core/setup.hpp"
#include "y/type/copy-of.hpp"

namespace Yttrium
{
    namespace GZip
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
            //! generic gzFile creation
            /**
             \param fileName compatible fileName
             \param mode     desired mode
             */
            explicit File(const char * const fileName, const char * const mode);
            virtual ~File() noexcept;

        protected:
            void * const gz; //!< handle

        private:
            Y_Disable_Copy_And_Assign(File); //!< discarding
        };

    }
}

#endif

