
//! \file

#ifndef Y_Core_PrintTableau_Included
#define Y_Core_PrintTableau_Included 1


#include "y/core/setup.hpp"
#include <iostream>

namespace Yttrium
{

    namespace Core
    {
        //______________________________________________________________________
        //
        //
        //! inline Display as vector of transformed data
        /**
         \param os        output stream
         \param iter      any valid iterator with '++' and '*' operators
         \param n         number of items to display
         \param transform transform value before printing
         \return output stream
         */
        //______________________________________________________________________
        template <typename ITERATOR,typename TRANSFORM> inline
        std::ostream & PrintTableau(std::ostream &os, ITERATOR iter, const size_t n, TRANSFORM &transform)
        {

            if(n>0)
            {
                os << ' ' << transform(*iter);
                for(size_t i=n-1;i>0;--i)
                    os << ",\n " << transform( *(++iter) );
            }
            return os;
        }

    }

}


#endif // !Y_Core_PrintTableau_Included
