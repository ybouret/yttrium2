
//! \file

#ifndef Y_Counted_Included
#define Y_Counted_Included 1

#include "y/core/setup.hpp"

namespace Yttrium
{
    //__________________________________________________________________________
    //
    //
    //
    //! Simplest Counted class for counting intrusive pointers
    //
    //
    //__________________________________________________________________________
    class Counted
    {
    public:
        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
        explicit Counted() noexcept; //!< setup
        virtual ~Counted() noexcept; //!< cleanup

        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________
        void   withhold() noexcept;         //!< ++nref
        bool   liberate() noexcept;         //!< \return --nref<=0
        size_t quantity() const noexcept;   //!< \return nref

    private:
        Y_Disable_Copy_And_Assign(Counted); //!< discarding
        size_t nref;                        //!< current ref count
    };
};

#endif
