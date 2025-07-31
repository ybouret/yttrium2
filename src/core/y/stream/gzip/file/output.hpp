//! \file

#ifndef Y_GZIP_OutputFile_Included
#define Y_GZIP_OutputFile_Included 1

#include "y/stream/gzip/file.hpp"

namespace Yttrium
{
    namespace GZip
    {


        class OutputMode
        {
        public:
            virtual ~OutputMode() noexcept;
            
        protected:
            explicit OutputMode(const unsigned level,
                                const bool     append);

            char mode[sizeof(void*)];
        private:
            Y_Disable_Copy_And_Assign(OutputMode);
        };
        //______________________________________________________________________
        //
        //
        //
        //! gzFile in input mode
        //
        //
        //______________________________________________________________________
        class OutputFile : public OutputMode, File
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit OutputFile(const char * const fileName,
                                const unsigned     level,
                                const bool         append); //!< open \param fileName compatible file
            virtual ~OutputFile() noexcept;                  //!< cleanup

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
        protected:
            void flush_();
            void write_(const char);
            
        private:
            Y_Disable_Copy_And_Assign(OutputFile); //!< discarding
        };

    }
}

#endif
