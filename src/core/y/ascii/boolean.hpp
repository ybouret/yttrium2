
//! \file

#ifndef Y_ASCII_Boolean_Included
#define Y_ASCII_Boolean_Included 1

#include "y/core/setup.hpp"

namespace Yttrium
{

    namespace ASCII
    {
        //______________________________________________________________________
        //
        //
        //
        //! bool to humand readable text
        //
        //
        //______________________________________________________________________
        struct Boolean
        {
            //! conversion
            /** \param flag \return "True|False" */
            static const char *Text(const bool flag) noexcept;

            //! conversion
            /** \param flag \return "true|false" */
            static const char *text(const bool flag) noexcept;

        };
    }

}

#endif // !Y_ASCII_Boolean_Included

