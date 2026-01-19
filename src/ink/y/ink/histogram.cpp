#include "y/ink/histogram.hpp"
#include <cstring>

namespace Yttrium
{
    namespace Ink
    {

        Histogram:: ~Histogram() noexcept
        {
            ldz();
        }

        Histogram:: Histogram() noexcept :
        bin()
        {
            ldz();
        }

        Histogram & Histogram:: ldz() noexcept
        {
            memset(bin,0,sizeof(bin));
            return *this;
        }

        Histogram::Type & Histogram:: operator[](const uint8_t b) noexcept
        {
            return bin[b];
        }

        const Histogram::Type & Histogram:: operator[](const uint8_t b) const noexcept
        {
            return bin[b];
        }

        Histogram & Histogram:: operator+= (const Type * const arr) noexcept
        {
            assert(0!=arr);
            for(size_t i=0;i<Bins;++i)
                bin[i] += arr[i];
            return *this;
        }


    }

}
