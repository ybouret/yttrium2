

#if defined(_MSC_VER)
#pragma warning ( disable : 4464 )
#endif

#include "y/stream/bzip2/file.hpp"
#include "../../../../y/bzip2/bzlib.h"

namespace Yttrium
{
    namespace BZip2
    {

        const char * const File:: CallSign = "BZip2";

        const char * File:: ErrorText(const int err) noexcept
        {
            switch(err)
            {
                    Y_Return_Named_Case(BZ_OK              );
                    Y_Return_Named_Case(BZ_RUN_OK          );
                    Y_Return_Named_Case(BZ_FLUSH_OK        );
                    Y_Return_Named_Case(BZ_FINISH_OK       );
                    Y_Return_Named_Case(BZ_STREAM_END      );
                    Y_Return_Named_Case(BZ_SEQUENCE_ERROR  );
                    Y_Return_Named_Case(BZ_PARAM_ERROR     );
                    Y_Return_Named_Case(BZ_MEM_ERROR       );
                    Y_Return_Named_Case(BZ_DATA_ERROR      );
                    Y_Return_Named_Case(BZ_DATA_ERROR_MAGIC);
                    Y_Return_Named_Case(BZ_IO_ERROR        );
                    Y_Return_Named_Case(BZ_UNEXPECTED_EOF  );
                    Y_Return_Named_Case(BZ_OUTBUFF_FULL    );
                    Y_Return_Named_Case(BZ_CONFIG_ERROR    );
                default:
                    break;
            }
            return Core::Unknown;
        }

        File:: File() noexcept
        {
        }
        
        File:: ~File() noexcept
        {

        }
    }
}
