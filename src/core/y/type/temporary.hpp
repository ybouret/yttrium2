//! \file

#ifndef Y_Type_Temporary_Included
#define Y_Type_Temporary_Included 1

#include "y/type/args.hpp"

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //! assigning temporary values
    //
    //__________________________________________________________________________
    template <typename T>
    class Temporary
    {
    public:
        Y_Args_Declare(T,Type); //!< aliases

        //! saving old value, assigning new one, assuming no exception
        /**
         \param target current target
         \param value  temporary value to assign
         */
        inline explicit Temporary(Type &target, ParamType value) noexcept :
        host(target), save(target) { target  = value; }

        //! restore saved value
        inline virtual ~Temporary() noexcept { host = save; }

    private:
        Y_Disable_Copy_And_Assign(Temporary); //!< discarding
        Type      &host; //!< initial persistent target
        ConstType  save; //!< initial data
    };
}



#endif // !Y_Type_Temporary_Included
