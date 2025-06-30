
//! \file

#ifndef Y_Apex_Metrics_Included
#define Y_Apex_Metrics_Included 1

#include "y/apex/types.hpp"
#include "y/calculus/integer-log2.hpp"
#include "y/memory/page.hpp"
#include "y/calculus/base2.hpp"

namespace Yttrium
{
    namespace Apex
    {

        //______________________________________________________________________
        //
        //
        //
        //! Metrics for Natural
        //
        //
        //______________________________________________________________________
        struct Metrics
        {
            typedef natural_t      Word;                                      //!< alias
            static const unsigned  WordBytes = sizeof(Word);                  //!< alias
            static const unsigned  WordShift = IntegerLog2<WordBytes>::Value; //!< alias
            static const size_t    MinBytes  = sizeof(Memory::Page);          //!< alias
            static const unsigned  MinShift  = IntegerLog2<MinBytes>::Value;  //!< alias
            static const size_t    MaxBytes  = Base2<size_t>::MaxBytes;       //!< alias
            static const unsigned  MaxShift  = Base2<size_t>::MaxShift;       //!< alias
            static const unsigned  Views     = WordShift+1;                   //!< alias
            
            //!
            /**
             \param bytes request
             \param shift adjusted
             \return 2^shift >= Max(bytes,MinBytes)
             */
            static size_t BytesFor(size_t bytes, unsigned &shift);

            //! raise exception on bytes overflow
            static void Overflow(const size_t);
        };

    }
}

#endif

