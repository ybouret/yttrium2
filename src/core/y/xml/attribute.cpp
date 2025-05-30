
#include "y/xml/attribute.hpp"
#include <iostream>

namespace Yttrium
{
    namespace XML
    {
        Attribute:: ~Attribute() noexcept
        {
            Coerce(hName) = 0;
            Coerce(hData) = 0;
            Coerce(dName) = 0;
            Coerce(dData) = 0;
            Coerce(width) = 0;

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

