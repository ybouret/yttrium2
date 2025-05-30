
#include "y/xml/element.hpp"
#include <iostream>

namespace Yttrium
{
    namespace XML
    {

        Element:: ~Element() noexcept
        {
        }

        Element:: Element() noexcept
        {
        }


        std::ostream & Element:: initProlog(std::ostream &os, const size_t indent) const
        {
            return Indent(os,indent) << Syntax::LANGLE << callSign();
        }

        std::ostream & Element:: initEpilog(std::ostream &os, const bool standAlone) const
        {
            if(standAlone) os << Syntax::SLASH;
            return os << Syntax::RANGLE;
        }



        std::ostream & Element:: init(std::ostream &os, const size_t indent) const
        {
            return initEpilog(initProlog(os,indent),false);
        }

        std::ostream & Element:: quit(std::ostream &os, const size_t indent) const
        {
            return Indent(os,indent) << Syntax::LANGLE << Syntax::SLASH << callSign() << Syntax::RANGLE;
        }


    }
}
