
//! \file

#ifndef Y_Libc_InputFile_Included
#define Y_Libc_InputFile_Included 1

#include "y/stream/input.hpp"
#include "y/stream/libc/types.hpp"
#include "y/string/fwd.hpp"

namespace Yttrium
{
    namespace Libc { class InputFile; }

    //__________________________________________________________________________
    //
    //
    //
    //! Libc Input Stream
    //
    //
    //__________________________________________________________________________
    class InputFile : public InputStream
    {
    public:
        class Code;
        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
        explicit InputFile(const char * const         fileName); //!< setup \param fileName fopen(fileName)
        explicit InputFile(const Core::String<char> & fileName); //!< setup \param fileName fopen(fileName.c_str())
        explicit InputFile(const StdIn_ &);              //!< setup from stdin
        virtual ~InputFile() noexcept;                   //!< cleanup


        //______________________________________________________________________
        //
        //
        // Interfacae
        //
        //______________________________________________________________________
        virtual bool query(char &C);
        virtual void store(const char C);

        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________

        Libc::InputFile & operator*() noexcept;

    private:
        Y_Disable_Copy_And_Assign(InputFile); //!< discarding
        Libc::InputFile * const file;         //!< low-level file
    };

}

#endif // !Y_Libc_InputFile_Included
