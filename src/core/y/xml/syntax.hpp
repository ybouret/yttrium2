//! \file

#ifndef Y_XML_Format_Included
#define Y_XML_Format_Included 1

#include "y/core/setup.hpp"

namespace Yttrium
{
    namespace XML
    {
        //______________________________________________________________________
        //
        //
        //! common syntax helpers
        //
        //______________________________________________________________________
        struct Syntax
        {
            static const char LANGLE = '<'; //!< alias
            static const char RANGLE = '>'; //!< alias
            static const char SLASH  = '/'; //!< alias
            static const char DQUOTE = '"'; //!< alias
        };

        //! pre-indent output stream
        /**
         \param os output stream
         \param indentation will be twice its count of spaces
         \return os
         */
        std::ostream & Indent(std::ostream &os, const size_t indentation);

    }
}

#endif

