
//! \file

#ifndef Y_RTLD_Soak_Included
#define Y_RTLD_Soak_Included 1

#include "y/rtld/dso.h"
#include "y/exception.hpp"
#include <cassert>

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //! Shared Object Application Kernel
    //
    //
    //__________________________________________________________________________
    template <typename CLASS>
    class Soak
    {
    public:

        //! create new CLASS on DLL load
        static inline void Enter() noexcept
        {
            try
            {
                assert(0==App);
                App = new CLASS();
            }
            catch(...)
            {

            }
        }

        //! delete on DLL unload
        static inline void Leave() noexcept
        {
            if(App)
            {
                delete App;
                App = 0;
            }
        }

        static CLASS * App;              //!< dll main object

    private:
        Y_Disable_Copy_And_Assign(Soak); //!< discarding

    };

    template <typename CLASS>
    CLASS * Soak<CLASS>:: App = 0;

    //! I/O for dll embedded class
#define Y_Soak(CLASS) \
Y_DLL_SETUP(Yttrium::Soak<CLASS>::Enter,Yttrium::Soak<CLASS>::Leave) Y_DLL_EXTERN()     \
Y_EXPORT bool Y_DLL_API CLASS##WasInit() noexcept { return Yttrium::Soak<CLASS>::App; } \
Y_DLL_FINISH() \

}

#endif

