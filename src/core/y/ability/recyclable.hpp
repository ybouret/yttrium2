//! \file

#ifndef Y_Type_Recyclable_Included
#define Y_Type_Recyclable_Included 1

#include "y/core/setup.hpp"

namespace Yttrium
{
    //__________________________________________________________________________
    //
    //
    //
    //! get a free() method
    //
    //
    //__________________________________________________________________________
    class Recyclable
    {
        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
    protected:
        explicit Recyclable() noexcept;
    public:
        virtual ~Recyclable() noexcept;


        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________

        //! free content, keep resources
        virtual void free() noexcept = 0;

    private:
        Y_Disable_Copy_And_Assign(Recyclable); //!< discarding
    };

}

#endif

