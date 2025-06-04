

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

        //! gc(All)
        virtual void release() noexcept;


        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________

        //! compute amount of total
        /**
         \return (amount*total)/255
         */
        static size_t Take(const uint8_t amount, const size_t total) noexcept;

        
        static size_t NewSize(const uint8_t amount, const size_t oldSize) noexcept;




    private:
        Y_Disable_Copy_And_Assign(Collectable); //!< discarding
    };

}

#endif
