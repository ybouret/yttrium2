
#include "y/ascii/convert.hpp"
#include "y/system/exception.hpp"
#include <cerrno>

namespace Yttrium
{

    namespace ASCII
    {
        namespace Conversion
        {
            void Parsing:: Overflow()
            {
                throw Libc::Exception(EDOM,"ASCII::Conversion overflow");
            }
        }
    }

}
