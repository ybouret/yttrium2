#include "y/information/entropy.hpp"
#include "y/container/ordered/static-priority-queue.hpp"
#include "y/check/usual.hpp"
#include <cstring>
#include <cmath>

namespace Yttrium
{

    namespace Information
    {

        void Entropy:: ldz() noexcept
        {
            memset(bin,0,sizeof(bin));
        }

        Entropy:: Entropy() noexcept : bin()
        {
            ldz();
        }

        Entropy:: ~Entropy() noexcept
        {

        }

        Entropy:: Entropy(const Entropy &other) noexcept :
        OutputStream(), bin()
        {
            memcpy(bin,other.bin,sizeof(bin));
        }

        Entropy & Entropy:: operator=(const Entropy &other)
        {
            memmove(bin, other.bin, sizeof(bin) );
            return *this;
        }

        void Entropy:: write(const char C)
        {
            ++bin[ uint8_t(C) ];
        }

        void Entropy:: flush()
        {
        }

        void Entropy:: frame(const void *const entry, const size_t count)
        {
            assert( Good(entry,count) );
            const uint8_t *p = (const uint8_t *)entry;
            for(size_t i=count;i>0;--i)
                ++bin[ *(p++) ];
        }

        long double Entropy:: operator()(void) const
        {


            uint64_t sum = 0;
            for(size_t i=0;i<256;++i) sum += bin[i];
            if(sum<=0) return 0;

            StaticPriorityQueue<long double,256, Sign::DecreasingComparator<long double> > pq;
            for(size_t i=0;i<256;++i)
            {
                const uint64_t n = bin[i];
                if(n>0)
                {
                    const long double p = ((long double)n) / sum;
                    const long double q =  -p * std::log(p);
                    pq << q;
                    //std::cerr << pq << "@" << pq->peek() << std::endl;
                }
            }
            assert(pq->size>0);
            while(pq->size>1)
            {
                const long double first = pq.pop();
                const long double second = pq.pop();
                pq << (first+second);
               // std::cerr << pq << "@" << pq->peek() << std::endl;
            }
            return pq.pop();

        }


    }

}
