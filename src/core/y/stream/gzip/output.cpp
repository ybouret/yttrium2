
#include "y/stream/gzip/output.hpp"

namespace Yttrium
{
    namespace GZip
    {

        Output:: ~Output() noexcept
        {
        }


        Output:: Output(const char * const fileName, const unsigned level, const bool append) :
        OutputFile(fileName, level, append),
        OutputStream()
        {
        }

        Output:: Output(const String & fileName, const unsigned level, const bool append) :
        OutputFile(fileName.c_str(), level, append),
        OutputStream()
        {
        }

        void Output:: flush()
        {
            flush_();
        }

        void Output:: write(const char c)
        {
            write_(c);
        }

    }

}

