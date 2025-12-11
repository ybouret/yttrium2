//! \file

#ifndef Y_Counted_Object_Included
#define Y_Counted_Object_Included 1

#include "y/object.hpp"
#include "y/counted.hpp"


namespace Yttrium
{
    //__________________________________________________________________________
    //
    //
    //
    //! Counted Object
    //
    //
    //__________________________________________________________________________
    class CountedObject : public Object, public Counted
    {
    public:
        explicit CountedObject() noexcept; //!< setup
        virtual ~CountedObject() noexcept; //!< cleanup
    private:
        Y_Disable_Copy_And_Assign(CountedObject); //!< discarding
    };
    
}

#endif // !Y_Counted_Object_Included

