//! \file

#ifndef Y_Type_Momentary_Included
#define Y_Type_Momentary_Included 1

#include "y/type/temporary.hpp"

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //! temporary helpers
    //
    //__________________________________________________________________________
    struct Momentary
    {
        //! force a flag to TRUE during a scope
        class On : public Temporary<bool>
        {
        public:
            explicit On(bool &) noexcept; //!< setup
            virtual ~On()       noexcept; //!< restore
        private:
            Y_Disable_Copy_And_Assign(On); //!< discardin
        };

        //! force a flag to FALSE during a scope
        class Off : public Temporary<bool>
        {
        public:
            explicit Off(bool &) noexcept; //!< setup
            virtual ~Off()       noexcept; //!< restore
        private:
            Y_Disable_Copy_And_Assign(Off); //!< discarding
        };

    };
    

}

#endif
