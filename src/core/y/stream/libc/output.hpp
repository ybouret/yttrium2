

//! \file

#ifndef Y_Libc_OutputFile_Included
#define Y_Libc_OutputFile_Included 1

#include "y/stream/output.hpp"
#include "y/stream/libc/types.hpp"
#include "y/string/fwd.hpp"

namespace Yttrium
{
    namespace Libc { class OutputFile; }

    //__________________________________________________________________________
    //
    //
    //
    //! Output FILE
    //
    //
    //__________________________________________________________________________
    class OutputFile : public OutputStream
    {
    public:
        class Code;
        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________

        //! open a disk FILE
        /**
         \param fileName file name
         \param append   in append mode iff true
         */
        explicit OutputFile(const char * const fileName, const bool append=false);
        explicit OutputFile(const Core::String<char> & , const bool=false); //!< wrapper
        explicit OutputFile(const StdOut_ &); //!< stdout
        explicit OutputFile(const StdErr_ &); //!< stdin
        virtual ~OutputFile() noexcept;       //!< cleanup

        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________
        virtual void write(const char); //!< write a char
        virtual void flush();           //!< flush attempt
        virtual void frame(const void * const, const size_t);
        
    private:
        Y_Disable_Copy_And_Assign(OutputFile); //!< discarding
        Libc::OutputFile * const file;         //!< low-level file
    };

    //__________________________________________________________________________
    //
    //
    //
    //! Output File in append mode
    //
    //
    //__________________________________________________________________________
    class AppendFile : public OutputFile
    {
    public:
        explicit AppendFile(const char * const); //!< setup
        virtual ~AppendFile() noexcept;          //!< cleanup

    private:
        Y_Disable_Copy_And_Assign(AppendFile); //!< discarding
    };

}

#endif
