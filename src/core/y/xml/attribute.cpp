
#include "y/xml/attribute.hpp"
#include <iostream>

namespace Yttrium
{
    namespace XML
    {
        Attribute:: ~Attribute() noexcept
        {
        }

        Attribute:: Attribute(const Attribute &_) noexcept :
        hName(_.hName),
        hData(_.hData),
        width(_.width),
        dName(_.dName),
        dData(_.dData)
        {
        }

        std::ostream & operator<<(std::ostream &os, const Attribute &attr)
        {
            os << ' ';
            attr.dName(os,attr.hName);
            os << '=' << Syntax::DQUOTE;
            attr.dData(os,attr.hData,attr.width);
            os << Syntax::DQUOTE;
            return os;
        }

    }

}

