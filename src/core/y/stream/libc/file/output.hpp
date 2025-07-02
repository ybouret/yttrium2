

//! \file

#ifndef Y_Libc_File_Output_Included
#define Y_Libc_File_Output_Included 1

#include "y/stream/libc/file/buffer.hpp"

namespace Yttrium
{
    namespace Libc
    {

        //______________________________________________________________________
        //
        //
        //
        //! low-level output file
        //
        //
        //______________________________________________________________________
        class OutputFile : public File
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
             \param userFile    valid FILE
             \param closeOnQuit if must close
             */
            explicit OutputFile(FILE * const userFile, const bool closeOnQuit);

            //! cleanup
            virtual ~OutputFile() noexcept;

            //__________________________________________________________________
            //
            //
            // methods
            //
            //__________________________________________________________________
            void flush();                                 //!< fflush
            void write(const char);                       //!< fwrite 1 char
            void frame(const void * const, const size_t); //!< fwrite all

        private:
            Y_Disable_Copy_And_Assign(OutputFile); //!< discarding
        };


        //______________________________________________________________________
        //
        //
        //
        //! File on disk
        //
        //
        //______________________________________________________________________
        class RegularOutputFile : public FileBuffer, public OutputFile
        {
        public:
            explicit RegularOutputFile(FILE * const); //!< setup from fopen
            virtual ~RegularOutputFile() noexcept;    //!< flcose

        private:
            Y_Disable_Copy_And_Assign(RegularOutputFile); //!< discarding
        };

        //______________________________________________________________________
        //
        //
        //
        //! stdout
        //
        //
        //______________________________________________________________________
        class StandardOutputFile : public OutputFile
        {
        public:
            explicit StandardOutputFile();          //!< setup
            virtual ~StandardOutputFile() noexcept; //!< cleanup

        private:
            Y_Disable_Copy_And_Assign(StandardOutputFile); //!< discarding
        };

        //______________________________________________________________________
        //
        //
        //
        //! stderr
        //
        //
        //______________________________________________________________________
        class StandardErrorFile : public OutputFile
        {
        public:
            explicit StandardErrorFile();          //!< setup
            virtual ~StandardErrorFile() noexcept; //!< cleanup

        private:
            Y_Disable_Copy_And_Assign(StandardErrorFile); //!< discarding
        };

    }

}

#endif
