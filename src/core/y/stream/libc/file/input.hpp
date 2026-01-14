
//! \file

#ifndef Y_Libc_File_Input_Included
#define Y_Libc_File_Input_Included 1

#include "y/stream/libc/file.hpp"
#include "y/stream/io/chars.hpp"
#include "y/stream/libc/file/buffer.hpp"


namespace Yttrium
{
    namespace Libc
    {

        

        //______________________________________________________________________
        //
        //
        //
        //! low-level input file
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

            //! setup
            /**
             \param userFile    valid FILE
             \param closeOnQuit if must close
             */
            explicit InputFile(FILE * const userFile,
                               const bool   closeOnQuit);

            //! cleanup
            virtual ~InputFile() noexcept;

            //__________________________________________________________________
            //
            //
            // methods
            //
            //__________________________________________________________________
            bool query(char &C);      //!< \param C char to get \return true iff success
            void store(const char C); //!< use internal Q to store \param C read character

        private:
            Y_Disable_Copy_And_Assign(InputFile); //!< discarding
            IO::Chars Q; //!< local queue for caching
        };

        //______________________________________________________________________
        //
        //
        //
        //! File on disk
        //
        //
        //______________________________________________________________________
        class RegularInputFile : public FileBuffer, public InputFile
        {
        public:
            explicit RegularInputFile(FILE * const); //!< setup from fopen(...)
            virtual ~RegularInputFile() noexcept;    //!< fclose

        private:
            Y_Disable_Copy_And_Assign(RegularInputFile);//!< discarding
        };


        //______________________________________________________________________
        //
        //
        //
        //! stdin
        //
        //
        //______________________________________________________________________
        class StandardInputFile : public InputFile
        {
        public:
            explicit StandardInputFile();          //!< setup from stdin
            virtual ~StandardInputFile() noexcept; //!< cleanup

        private:
            Y_Disable_Copy_And_Assign(StandardInputFile); //!< discarding
        };

    }

}

#endif // !Y_Libc_File_Input_Included
