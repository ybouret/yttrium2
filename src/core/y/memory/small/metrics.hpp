
//! \file

#ifndef Y_Memory_Object_Metrics_Included
#define Y_Memory_Object_Metrics_Included 1

#include "y/calculus/integer-log2.hpp"

namespace Yttrium
{
    namespace Memory
    {

        namespace Small
        {
            //__________________________________________________________________
            //
            //
            //
            //! pre-computed metric for Object::Factory and Quanta
            //
            //
            //__________________________________________________________________
            struct Metrics
            {
                static const size_t   DefaultPageBytes = 4096;                                 //!< default page size
                static const unsigned DefaultPageShift = IntegerLog2<DefaultPageBytes>::Value; //!< ensure power of two
                static const size_t   LimitObjectBytes = 512;                                  //!< limit size for small objects
                static const unsigned LimitObjectShift = IntegerLog2<LimitObjectBytes>::Value; //!< ensure power of two
                static const size_t   MediumLimitBytes;                                        //!< Segment::MaxSizeFor(DefaultPageShift)
            };
            
        }

    }

}

#endif
