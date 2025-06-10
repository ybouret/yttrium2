
//! \file

#ifndef Y_Caching_Included
#define Y_Caching_Included 1

#include "y/ability/collectable.hpp"

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //! Caching : put in cache and Collectable
    //
    //
    //__________________________________________________________________________
    class Caching : public Collectable
    {
        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
    protected:
        explicit Caching() noexcept; //!< setup
    public:
        virtual ~Caching() noexcept; //!< cleanup

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
        virtual void   cache(const size_t)    = 0; //!< try to cache some data
        virtual size_t count() const noexcept = 0; //!< available data \return data in cache

    private:
        Y_Disable_Copy_And_Assign(Caching); //!< discarding
    };

}

#endif
