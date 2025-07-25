//! \file

#ifndef Y_Associative_Included
#define Y_Associative_Included 1

#include "y/type/args.hpp"
#include "y/ability/recyclable.hpp"

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //! associative container interface
    //
    //
    //__________________________________________________________________________
    template <typename KEY, typename T>
    class Associative : public Recyclable
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        Y_Args_Expose(T,Type);   //!< aliases
        Y_Args_Declare(KEY,Key); //!< aliases

        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________
        virtual ConstType * search(ParamKey) const noexcept = 0; //!< \return search for key
        virtual Type *      search(ParamKey)       noexcept = 0; //!< \return search for key, with optional prefetch
        virtual bool        remove(ParamKey)       noexcept = 0; //!< \return true iff key was found and item was removed

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
    protected:
        inline explicit Associative() noexcept {} //!< setup

    public:
        inline virtual ~Associative() noexcept {} //!< cleanup

    private:
        Y_Disable_Copy_And_Assign(Associative); //!< discarding
    };

}

#endif

