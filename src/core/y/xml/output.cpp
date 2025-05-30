
#include "y/xml/output.hpp"
#include <iostream>

namespace Yttrium
{
    namespace XML
    {

        Output:: ~Output() noexcept
        {
        }

        Output:: Output() noexcept  
        {
        }


        std::ostream & Output:: initProlog(std::ostream &os, const size_t indent) const
        {
            return Indent(os,indent) << Format::LANGLE << callSign();
        }

        std::ostream & Output:: initEpilog(std::ostream &os, const bool standAlone) const
        {
            if(standAlone) os << Format::SLASH;
            return os << Format::RANGLE;
        }



        std::ostream & Output:: init(std::ostream &os, const size_t indent) const
        {
            return initEpilog(initProlog(os,indent),false);
        }

        std::ostream & Output:: quit(std::ostream &os, const size_t indent) const
        {
            return Indent(os,indent) << Format::LANGLE << Format::SLASH << callSign() << Format::RANGLE;
        }


    }
}
