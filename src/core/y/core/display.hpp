
//! \file

#ifndef Y_Core_Display_Included
#define Y_Core_Display_Included 1


#include "y/container.hpp"
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
        std::ostream & Display(std::ostream &os, ITERATOR iter, const size_t n, TRANSFORM &transform)
        {
            os << Container::LBRACK;
            if(n>0)
            {
                os << transform(*iter);
                for(size_t i=n-1;i>0;--i)
                    os << Container::SEMICOLON << transform( *(++iter) );
            }
            return os << Container::RBRACK;
        }


        //______________________________________________________________________
        //
        //
        //! inline Display as vector of raw data
        /**
         \param os        output stream
         \param iter      any valid iterator with '++' and '*' operators
         \param n         number of items to display
         \param transform transform value before printing
         \return output stream
         */
        //______________________________________________________________________
        template <typename ITERATOR> inline
        std::ostream & Display(std::ostream &os, ITERATOR iter, const size_t n)
        {
            os << Container::LBRACK;
            if(n>0)
            {
                os << *iter;
                for(size_t i=n-1;i>0;--i)
                    os << Container::SEMICOLON << ( *(++iter) );
            }
            return os << Container::RBRACK;
        }


    }

}

#endif
