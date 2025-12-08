
//! \file

#ifndef Y_Libc_File_Copy_Included
#define Y_Libc_File_Copy_Included 1

#include "y/stream/libc/input.hpp"
#include "y/stream/libc/output.hpp"


namespace Yttrium
{
    namespace Hashing { class Function; }

    namespace Libc
    {
        //______________________________________________________________________
        //
        //
        //
        //! buffered file copy
        //
        //
        //______________________________________________________________________
        struct FileCopy
        {

            static void Run(OutputFile &, InputFile &, Hashing::Function * const); //!< low-level copy
            static void Run(Yttrium::OutputFile &, Yttrium::InputFile &, Hashing::Function * const); //!< high-level copy

            //! merge content
            /**
             \param output opened file
             \param args   argument for InputFile constructor
             \param H      optional hashing function for on-the-fly update
             */
            template <typename ARGS> static inline
            void Merge(Yttrium::OutputFile &output, const ARGS &args, Hashing::Function * const H = 0) {
                Yttrium::InputFile input(args);
                Run(output,input,H);
            }


        };
    }
}

#endif // !Y_Libc_File_Copy_Included

