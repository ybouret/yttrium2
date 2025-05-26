

//! \file

#ifndef Y_Legacy_String_Included
#define Y_Legacy_String_Included 1

#include "y/core/setup.hpp"
#include "y/ostream-proto.hpp"

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //! get a c_str()
    //
    //
    //__________________________________________________________________________
    class LegacyString
    {
    protected:
        explicit LegacyString() noexcept; //!< setup
        virtual ~LegacyString() noexcept; //!< cleanup

    public:

        //! get human readadble string
        /** \return '\0' terminated C string */
        virtual const char * c_str() const noexcept = 0;

        //! default output
        Y_OSTREAM_PROTO(LegacyString);

    private:
        Y_Disable_Copy_And_Assign(LegacyString); //!< discarding
    };

}

#endif

