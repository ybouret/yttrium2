#include "y/string/percent.hpp"
#include "y/system/exception.hpp"
#include "y/string/format.hpp"
#include <cmath>

namespace Yttrium
{

    String StringPercent:: APGet(const apn &count, const apn &total)
    {
        static const char func[] = "StringPercent";
        static const char done[] = "100.00%";

        if(total<=0)
        {
            if(count>0) throw Specific::Exception(func,"division of %s by zero", count.decString().c_str() );
            return done;
        }
        else
        {
            switch( apn::Compare(count,total) )
            {
                case Positive: throw Specific::Exception(func,"%s exceeds %s", count.decString().c_str(), total.decString().c_str());
                case __Zero__: return done;
                case Negative:
                    break;;
            }

            const float p = floorf(apn::Ratio<float>(count,total) * 10000.0f+0.5f)/100.0f;
            return Formatted::Get("%6.2f%%",p);
        }
    }

}
