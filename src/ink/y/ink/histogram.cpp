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


        Histogram & Histogram:: operator+= (const Histogram &H) noexcept
        {
            return (*this) += H.bin;
        }

        bool operator==(const Histogram &lhs, const Histogram &rhs) noexcept
        {
            return (&lhs == &rhs) || 0 == memcmp(lhs.bin, rhs.bin, Histogram::LocalMemory );
        }


    }

}

#include "y/stream/libc/output.hpp"
#include "y/string.hpp"
#include "y/format/decimal.hpp"

namespace Yttrium
{
    namespace Ink
    {
        void Histogram:: save(const String &fileName) const
        {
            OutputFile fp(fileName);
            for(unsigned i=0;i<256;++i)
            {
                fp << Decimal(i).c_str() << ' ' << Decimal(bin[i]).c_str() << '\n';
            }

        }

    }

}

