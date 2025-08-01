//! \file

#ifndef Y_String_Percent_Included
#define Y_String_Percent_Included 1

#include "y/string.hpp"
#include "y/apex/natural.hpp"

namespace Yttrium
{

    //! convert ratios to percent string
    struct StringPercent
    {

        //! \param num numerator \param den denominator \return percent of num<=den
        template <typename U, typename V> static
        inline String Get(const U &num, const V &den)
        {
            const apn count = num;
            const apn total = den;
            return APGet(count,total);
        }

        //! \param count numerator \param total denominator \return percent of count<=total
        static String APGet(const apn &count, const apn &total);
    };

}

#endif

