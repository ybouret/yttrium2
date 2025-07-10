//! \file

#ifndef Y_Human_Readable_Included
#define Y_Human_Readable_Included 1

#include "y/core/setup.hpp"
#include "y/ostream-proto.hpp"

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //! make Human Readable integer(s)
    //
    //
    //__________________________________________________________________________
    class HumanReadable
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________

        //! Divider
        struct Divider {
            char     suffix; //!<  ' '|k|M|G|T|P|E
            uint64_t factor; //!< 2^(0|10|20|30|40|50|60)
        };

        static const Divider Divide[]; //!< precomputed dividers
        static const size_t  Number;   //!< sizeof(Divide)/sizeof(Divide[0)
        

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
        HumanReadable(const HumanReadable &) noexcept; //!< copy
        HumanReadable(const uint64_t)        noexcept; //!< setup
        ~HumanReadable()                     noexcept; //!< cleanup
        Y_OSTREAM_PROTO(HumanReadable);                //!< display with 2 digits

        const unsigned quot; //!< quotient
        const unsigned rem;  //!< remainder
        const unsigned sfx;  //!< value = quot * 10^(3*sfx) + rem

    private:
        Y_Disable_Assign(HumanReadable); //!< discarding
    };
}

#endif

