
#ifndef Y_GZIP_InputFile_Included
#define Y_GZIP_InputFile_Included 1

#include "y/stream/gzip/file.hpp"

namespace Yttrium
{
    namespace GZip
    {

        //______________________________________________________________________
        //
        //
        //
        //! gzFile in input mode
        //
        //
        //______________________________________________________________________
        class InputFile : public File
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit InputFile(const char * const fileName); //!< open \param fileName compatible file
            virtual ~InputFile() noexcept;                   //!< cleanup

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            bool query1(char &); //!< \return true if one char was read


        private:
            Y_Disable_Copy_And_Assign(InputFile); //!< discarding
        };

    }
}

#endif
