
//! \file

#ifndef Y_Memory_Object_Metrics_Included
#define Y_Memory_Object_Metrics_Included 1

#include "y/calculus/integer-log2.hpp"

namespace Yttrium
{
    namespace Memory
    {

        namespace Object
        {

            struct Metrics
            {
                static const size_t   DefaultPageBytes = 4096;                                   //!< default page size
                static const unsigned DefaultPageShift = IntegerLog2<DefaultPageBytes>::Value; //!< ensure power of two
                static const size_t   LimitObjectBytes = 512;                                    //!< limit size
                static const unsigned LimitObjectShift = IntegerLog2<LimitObjectBytes>::Value; //!< ensure power of two
                //static const size_t   CONDENSATION_BYTES = 4;                                      //!< decrease complexity
               // static const unsigned CONDENSATION_SHIFT = IntegerLog2<CONDENSATION_BYTES>::Value; //!< ensure power of two
                static const size_t   MediumLimitBytes;                                          //!< Segment::MaxSizeFor(DefaultPageShift)
            };
            
        }

    }

}

#endif
