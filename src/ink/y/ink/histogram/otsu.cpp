
#include "y/ink/histogram/otsu.hpp"

namespace Yttrium
{
    namespace Ink
    {

        uint8_t Otsu:: Threshold(const Histogram &H) noexcept
        {
            typedef Histogram::Type htype;
            htype total = 0;
            htype sum   = 0;
            for(htype i=0;i<Histogram::Bins;++i)
            {
                const htype h = H[i];
                total += h;
                sum   += i*h;
            }


            htype sumB = 0;
            htype wB   = 0;

            double varMax    = 0;
            htype  threshold = 0;
            for(htype t=0;t<Histogram::Bins;++t)
            {
                const htype h = H[t];
                wB += h;                     if(wB<=0) continue;
                const htype wF = total - wB; if(wF<=0) break;
                sumB += t*h;
                const double mB         = (double)sumB / wB;
                const double mF         = (double)(sum-sumB) / wF;
                const double dmu        = mB - mF;
                const double varBetween = (double)wB * (double)wF * dmu*dmu;
                if(varBetween>varMax)
                {
                    varMax    = varBetween;
                    threshold = t;
                }
            }


            return (uint8_t)threshold;
        }
    }

}


