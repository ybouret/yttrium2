
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
            return Indent(os,indent) << Format::LANGLE << callSign();
        }

        std::ostream & Element:: initEpilog(std::ostream &os, const bool standAlone) const
        {
            if(standAlone) os << Format::SLASH;
            return os << Format::RANGLE;
        }



        std::ostream & Element:: init(std::ostream &os, const size_t indent) const
        {
            return initEpilog(initProlog(os,indent),false);
        }

        std::ostream & Element:: quit(std::ostream &os, const size_t indent) const
        {
            return Indent(os,indent) << Format::LANGLE << Format::SLASH << callSign() << Format::RANGLE;
        }


    }
}
