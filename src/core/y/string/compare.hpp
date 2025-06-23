

//!\ file


#ifndef Y_String_Compare_Included
#define Y_String_Compare_Included 1

#include "y/check/usual.hpp"
#include "y/type/sign.hpp"

namespace Yttrium
{

    template <typename T> inline
    bool StringAreEqual(const T * const lhs,
                        const size_t    lhsCount,
                        const T * const rhs,
                        const size_t    rhsCount) noexcept
    {
        assert( Good(lhs,lhsCount) );
        assert( Good(rhs,rhsCount) );

        return (lhsCount == rhsCount) && (0 == memcmp(lhs,rhs,lhsCount*sizeof(T)));
    }


    template <typename T> inline
    bool StringAreDifferent(const T * const lhs,
                            const size_t    lhsCount,
                            const T * const rhs,
                            const size_t    rhsCount) noexcept
    {
        assert( Good(lhs,lhsCount) );
        assert( Good(rhs,rhsCount) );

        return (lhsCount != rhsCount) || (0 != memcmp(lhs,rhs,lhsCount*sizeof(T)));
    }

    namespace Core
    {
        template <typename T> inline
        SignType StringCompareSmallLarge(const T *    small,
                                         const T *    large,
                                         const size_t count) noexcept
        {
            assert(Good(small,count));
            assert(Good(large,count));

        }
    }


    template <typename T> inline
    SignType StringCompare(const T * const lhs,
                           const size_t    lhsCount,
                           const T * const rhs,
                           const size_t    rhsCount) noexcept
    {
        assert( Good(lhs,lhsCount) );
        assert( Good(rhs,rhsCount) );
        bool opposite = false;
        const T * smallEntry = lhs;
        T         smallCount = lhsCount;
        const T * largeEntry = rhs;
        T         largeCount = rhsCount;
        if(largeCount<smallCount) {
            opposite = true;
            Swap(largeCount,smallCount);
            Swap(largeEntry,smallEntry);
        }

        for(size_t i=smallCount;i>0;--i)
        {
            switch( Sign::Of(*(smallEntry++), *(largeEntry++)))
            {
                case Negative: return opposite ? Positive : Negative;
                case Positive: return opposite ? Negative : Positive;
                case __Zero__: continue;
            }
        }



    }



}
#endif
