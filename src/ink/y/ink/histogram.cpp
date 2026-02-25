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


        static inline
        Histogram::Type Score(const Histogram::Type a, const Histogram::Type b) noexcept
        {
            if(a<b)
            {
                return b-a;
            }
            else
            {
                if(b<a)
                    return a-b;
                else
                    return 0;
            }
        }



        uint8_t Histogram:: find(const Quartile q, const uint8_t lo, const uint8_t up) const noexcept
        {
            assert(lo<=up);
            Type         sum[Bins]; // cumulative distribution
            const int jlo = lo;
            const int jup = up;
            sum[jlo] = bin[jlo];
            for(int j=jlo+1;j<=jup;++j) sum[j] = sum[j-1] + bin[j];

            // search parameters
            Type sQuery = sum[jup];
            int  jQuery = jlo+jup;

            switch(q)
            {
                case Q1:
                    sQuery /= 4;
                    jQuery = jlo + (jup-jlo)/4;
                    break;

                case Q2:
                    sQuery /= 2;
                    jQuery /= 2;
                    break;

                default:
                    (sQuery *= 3) /= 4;
                    jQuery = jlo + ( 3 * (jup-jlo) ) / 4;
                    break;
            }

            // search from jQuery
            int jopt = jQuery;
            {
                Type  best = Score(sQuery,sum[jopt]);
                for(int j=jQuery-1;j>=jlo;--j)
                {
                    const Type score = Score(sQuery,sum[j]);
                    if(score<best)
                    {
                        best = score;
                        jopt = j;
                    }
                }
                for(int j=jQuery+1;j<=jup;++j)
                {
                    const Type score = Score(sQuery,sum[j]);
                    if(score<best)
                    {
                        best = score;
                        jopt = j;
                    }
                }
            }
            assert(jlo<=jopt);
            assert(jopt<=jup);
            return (uint8_t) jopt;
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

        void Histogram:: save(const char * const fileName) const
        {
            const String _(fileName);
            save(_);
        }
    }

}

