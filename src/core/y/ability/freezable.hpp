
//! \file

#ifndef Y_Modifiable_Included
#define Y_Modifiable_Included 1

#include "y/core/setup.hpp"
#include "y/string/fwd.hpp"

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //! one way flag
    //
    //
    //__________________________________________________________________________
    class Freezable
    {
    public:
        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
        explicit Freezable() noexcept; //!< setup
        virtual ~Freezable() noexcept; //!< cleanup

        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________
        void freeze()       noexcept; //!< set frozen
        bool frozen() const noexcept; //!< \return true iff frozen

        void checkpoint(const char * const,         const char * const) const; //!< throw exception if frozen
        void checkpoint(const Core::String<char> &, const char * const) const; //!< throw exception if frozen

    private:
        Y_Disable_Copy_And_Assign(Freezable); //!< disarding
        bool flag; //!< frozen flag
    };

}
#endif

