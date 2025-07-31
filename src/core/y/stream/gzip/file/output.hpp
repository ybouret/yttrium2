//! \file

#ifndef Y_GZIP_OutputFile_Included
#define Y_GZIP_OutputFile_Included 1

#include "y/stream/gzip/file.hpp"

namespace Yttrium
{
    namespace GZip
    {

        //______________________________________________________________________
        //
        //
        //
        //! make output mode from parameters
        //
        //
        //______________________________________________________________________
        class OutputMode
        {
        public:
            virtual ~OutputMode() noexcept; //!< cleanup

        protected:
            //! setut \param level 0:9 \param append used append file
            explicit OutputMode(const unsigned level,
                                const bool     append);

            //! computed mode
            char mode[sizeof(void*)];
        private:
            Y_Disable_Copy_And_Assign(OutputMode); //!< discarding
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

            //! setup
            /**
             \param fileName output file name
             \param level in 0:9
             \param append if true, open fileName in append mode
             */
            explicit OutputFile(const char * const fileName,
                                const unsigned     level,
                                const bool         append);

            //! cleaup
            virtual ~OutputFile() noexcept;

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
        protected:
            void flush_();            //!< inner flush
            void write_(const char);  //!< inner write

        private:
            Y_Disable_Copy_And_Assign(OutputFile); //!< discarding
        };

    }
}

#endif
