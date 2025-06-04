

//! \file

#ifndef Y_Type_Collectable_Included
#define Y_Type_Collectable_Included 1

#include "y/ability/releasable.hpp"

namespace Yttrium
{
    //__________________________________________________________________________
    //
    //
    //
    //! May collect some garbage
    //
    //
    //__________________________________________________________________________
    class Collectable : public Releasable
    {
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
    public:
        static const uint8_t All = 0xff;

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
    protected:
        explicit Collectable() noexcept;
    public:
        virtual ~Collectable() noexcept;


        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________
        virtual void gc(const uint8_t amount) noexcept = 0;

        static size_t Mul(const uint8_t amount, const size_t total) noexcept;

        //! gc(All)
        virtual void release() noexcept;

    private:
        Y_Disable_Copy_And_Assign(Collectable); //!< discarding
    };

}

#endif
