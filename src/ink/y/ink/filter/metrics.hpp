
//! \file

#ifndef Y_Ink_Filter_Metrics_Included
#define Y_Ink_Filter_Metrics_Included 1

#include "y/type/sign.hpp"

namespace Yttrium
{
    namespace Ink
    {
        
        class FilterMetrics
        {
        public:
            static const char * const CallSign;

            explicit FilterMetrics(const size_t blockSize);
            virtual ~FilterMetrics() noexcept;

            template <typename T> static inline
            size_t Count(const T * const blockAddr, const size_t blockSize)
            {
                assert(0!=blockAddr);
                size_t res = 0;
                for(size_t i=0;i<blockSize;++i)
                {
                    switch( Sign::Of(blockAddr[i]) )
                    {
                        case __Zero__: continue;
                        case Negative:
                        case Positive:
                            ++res;
                            continue;
                    }
                }
                return res;
            }

            const size_t side;
            const unit_t delta;

        private:
            Y_Disable_Copy_And_Assign(FilterMetrics);
        };
    }

}

#endif // !Y_Ink_Filter_Metrics_Included

