//! \file

#ifndef Y_Stream_IO_Codec64_Included
#define Y_Stream_IO_Codec64_Included 1

#include "y/calculus/integer-log2.hpp"
#include "y/core/setup.hpp"

namespace Yttrium
{

    namespace IO
    {
        //! Metrics for Codec64
        struct Codec64
        {
            static const size_t   MaxExtraBytes  = sizeof(uint64_t);                    //!< 1+MaxExtraBytes in worst case scenario
            static const size_t   HeaderBits     = IntegerLog2<MaxExtraBytes>::Value+1; //!< bits to store extra bytes count
            static const size_t   HeaderRoll     = 8-HeaderBits;                        //!< room left in first byte for data bits
            static const uint64_t HeaderMask     = (1<<HeaderRoll)-1;                   //!< mask of HeaderRoll
        };
    };

}

#endif

