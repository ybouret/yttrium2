
//! \file

#ifndef Y_Libc_File_Copy_Included
#define Y_Libc_File_Copy_Included 1

#include "y/stream/libc/input.hpp"
#include "y/stream/libc/output.hpp"


namespace Yttrium
{
    namespace Libc
    {

        struct FileCopy
        {
            static void Run(OutputFile &, InputFile &);
            static void Run(Yttrium::OutputFile &, Yttrium::InputFile &);


            template <typename ARGS> static inline
            void Merge(Yttrium::OutputFile &output, const ARGS &args) {
                Yttrium::InputFile input(args);
                Run(output,input);
            }


        };
    }
}

#endif // !Y_Libc_File_Copy_Included

