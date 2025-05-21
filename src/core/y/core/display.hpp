
//! \file

#ifndef Y_Core_Display_Included
#define Y_Core_Display_Included 1

#include "y/system/compiler.hpp"
#include <iostream>

namespace Yttrium
{

    namespace Core
    {
        //______________________________________________________________________
        //
        //
        //! inline Display as vector of data
        /**
         \param os output stream
         \param iter any valid iterator with '++' and '*' operators
         \param n    number of items to display
         \return output stream
         */
        //______________________________________________________________________
        template <typename ITERATOR> inline
        std::ostream & Display( std::ostream &os, ITERATOR iter, const size_t n)
        {
            os << '[';
            if(n>0)
            {
                os << *iter;
                for(size_t i=n-1;i>0;--i)
                    os << ';' << *(++iter);
            }
            os << ']';
            return os;
        }
    }

}

#endif
