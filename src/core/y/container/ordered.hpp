

//! \file

#ifndef Y_Ordered_Included
#define Y_Ordered_Included 1

#include "y/container.hpp"
#include "y/type/args.hpp"

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //! Ordered Interface to expand CONTAINER ([Gradual|Dynamic]Container)
    //
    //
    //__________________________________________________________________________
    template <typename T, typename CONTAINER>
    class Ordered : public CONTAINER
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        Y_ARGS_DECL(T,Type); //!< aliases

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
    protected:
        //! setup
        inline explicit Ordered() noexcept : CONTAINER() {}

    public:
        //! cleanup
        inline virtual ~Ordered() noexcept {}

        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________
        virtual void push(ParamType) = 0; //!< push object into container
        virtual Type pop()           = 0; //!< remove top object

        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________
        Ordered & operator<<(ParamType rhs) { push(rhs); return *this; }


    private:
        Y_Disable_Copy_And_Assign(Ordered); //!< discarding
    };

}

#endif
