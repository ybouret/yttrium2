
#include "y/xml/syntax.hpp"

namespace Yttrium
{
    namespace XML
    {

        std::ostream & Indent(std::ostream &os, const size_t count)
        {
            return Core::Indent(os, count << 1, ' ');
        }
    }
}
