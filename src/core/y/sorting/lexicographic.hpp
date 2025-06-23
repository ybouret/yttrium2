

//! \file

#ifndef Y_Sorting_Lexicographic_Included
#define Y_Sorting_Lexicographic_Included 1

#include "y/type/sign.hpp"


namespace Yttrium
{

    namespace Sorting
    {
        namespace Inner
        {
            template <typename ITERATOR>
            inline SignType Lexicographic(ITERATOR small, const size_t smallCount,
                                          ITERATOR large, const size_t largeCount)
            {
                assert(smallCount<=largeCount);
                // test common part
                for(size_t i=smallCount;i>0;--i,++small,++large)
                {
                    switch( Sign::Of(*small,*large))
                    {
                        case Negative: return Negative;
                        case Positive: return Positive;
                        case __Zero__: continue;
                    }
                }
                if(smallCount>=largeCount)
                {
                    assert(smallCount==largeCount);
                    return __Zero__; // equality
                }
                else
                {
                    return Negative; // more data after same common part
                }
            }

        }

        template <typename ITERATOR>
        inline SignType Lexicographic(ITERATOR lhs, const size_t lhsCount,
                                      ITERATOR rhs, const size_t rhsCount)
        {
            if(lhsCount<=rhsCount)
                return Inner::Lexicographic(lhs, lhsCount, rhs, rhsCount);
            else
                return Sign::Opposite( Inner::Lexicographic(rhs, rhsCount, lhs, lhsCount) );
        }
    }

}

#endif

