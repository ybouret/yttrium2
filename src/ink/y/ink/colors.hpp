//! \file

#ifndef Y_Ink_Colors_Included
#define Y_Ink_Colors_Included 1

#include "y/color/conv.hpp"


namespace Yttrium
{
    namespace Ink
    {
        typedef Color::RGBA<uint8_t> RGBA; //!< alias
        typedef Color::RGB<uint8_t>  RGB;  //!< alias

        struct Channel
        {
            static const char * const Red;
            static const char * const Green;
            static const char * const Blue;
            static const char * const Alpha;
            static const char * const Name[4];
        };

    }

}

#endif // !Y_Ink_Colors_Included

