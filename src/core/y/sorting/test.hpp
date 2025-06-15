//! \file

#ifndef Y_Sorting_Test_Included
#define Y_Sorting_Test_Included 1

#include "y/type/sign.hpp"

namespace Yttrium{

    namespace Sorting
    {
        //! Testing that a range is sorted
        struct Test
        {
            //! test sorting with C++ comparison
            /**
             \param compare return SignType
             \param curr    first iterator
             \param size    range size
             \return true iff sorted
             */
            template <typename ITERATOR,typename COMPARE> static inline
            bool AccordingTo(COMPARE &compare, ITERATOR curr, size_t size)
            {
                switch(size)
                {
                    case 0:
                    case 1:
                        return true;
                    default:
                        break;
                }
                ITERATOR next = curr;
                for(++next,--size;size>0;--size,++curr,++next)
                {
                    if( Positive == compare(*curr,*next) ) return false;
                }
                return true;
            }
        };
    }

}

#endif

