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

        //! name channels
        struct Channel
        {
            static const char * const Red;     //!< "red"
            static const char * const Green;   //!< "green"
            static const char * const Blue;    //!< "blue"
            static const char * const Alpha;   //!< "alpha"
            static const char * const Name[4]; //!< names
        };

    }

}

#endif // !Y_Ink_Colors_Included

