
#include "y/ink/image/format.hpp"
#include "y/jive/regexp.hpp"

namespace Yttrium
{
    namespace Ink
    {

        Format:: ~Format() noexcept
        {
        }

        Jive::Pattern * Format:: MakePattern(String &rx)
        {
            return Jive::RegExp::Compile(((rx >> '(') << ')' << '&'));
        }

        void Format:: renderExtension() const
        {
            const String dotFile = name + ".dot";
            Vizible::Render(dotFile,*extension.motif);
        }


    }

}
