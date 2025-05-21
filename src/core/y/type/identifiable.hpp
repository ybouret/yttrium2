
//! \file

#ifndef Y_Type_Identifiable_Included
#define Y_Type_Identifiable_Included 1

#include "y/core/setup.hpp"

namespace Yttrium
{
    //__________________________________________________________________________
    //
    //
    //
    //! get a callSign
    //
    //
    //__________________________________________________________________________
    class Identifiable
    {
        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
    protected:
        explicit Identifiable() noexcept;
    public:
        virtual ~Identifiable() noexcept;


        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________

        //! get a c-style call sign
        /** \return a persistent call sign */
        virtual const char * callSign() const noexcept = 0;

    private:
        Y_Disable_Copy_And_Assign(Identifiable); //!< discarding
    };

}

#endif
