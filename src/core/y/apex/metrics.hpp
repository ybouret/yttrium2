
//! \file

#ifndef Y_Apex_Metrics_Included
#define Y_Apex_Metrics_Included 1

#include "y/apex/types.hpp"
#include "y/calculus/integer-log2.hpp"
#include "y/calculus/alignment.hpp"
#include "y/memory/page.hpp"
#include "y/calculus/base2.hpp"

namespace Yttrium
{
    namespace Apex
    {

        struct Metrics
        {
            typedef natural_t      Word;
            static const unsigned  WordBytes = sizeof(Word);
            static const unsigned  WordShift = IntegerLog2<WordBytes>::Value;
            typedef Alignment::OnLog2<WordShift> Aligned;
            static const size_t    MinBytes  = sizeof(Memory::Page);
            static const unsigned  MinShift  = IntegerLog2<MinBytes>::Value;
            static const size_t    MaxBytes  = Base2<size_t>::MaxBytes;
            static const unsigned  MaxShift  = Base2<size_t>::MaxShift;

            template <typename T> static inline
            size_t BytesToBlocksOf(size_t bytes)
            {
                if(bytes>MaxBytes) Overflow(bytes);
                if(bytes<MinBytes) bytes = MinBytes;
                return Aligned::Ceil( NextPowerOfTwo(bytes) ) / sizeof(T);
            }
            
            static void Overflow(const size_t);
        };

    }
}

#endif

