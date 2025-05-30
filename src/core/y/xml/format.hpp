//! \file

#ifndef Y_XML_Format_Included
#define Y_XML_Format_Included 1

#include "y/core/setup.hpp"

namespace Yttrium
{
    namespace XML
    {
        struct Format
        {
            static const char LANGLE = '<';
            static const char RANGLE = '>';
            static const char SLASH  = '/';
        };

        std::ostream & Indent(std::ostream &os, const size_t indentation);

    }
}

#endif

