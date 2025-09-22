
//! \file

#ifndef Y_RTLD_Soak_Included
#define Y_RTLD_Soak_Included 1

#include "y/rtld/soak/api.hpp"
#include <cassert>
#include <cstring>

namespace Yttrium
{


    template <typename CLASS>
    class Soak : public SoakAPI
    {
    protected:
        inline explicit Soak() noexcept : SoakAPI() {}

    public:
        inline virtual ~Soak() noexcept {}
        inline virtual const char * callSign() const noexcept { return CLASS:: CallSign; }

        

    private:
        Y_Disable_Copy_And_Assign(Soak);
        static CLASS * App;
    };

    template <typename CLASS> CLASS * Soak<CLASS>:: App = 0;



#if 0
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
        static const size_t MSGLEN = 256;

        //! create new CLASS on DLL load
        static inline void Enter() noexcept
        {
            try
            {
                assert(0==App);
                memset(What,0,sizeof(What));
                memset(When,0,sizeof(When));
                App = new CLASS();
            }
            catch(std::exception &excp)
            {
                strncpy(What,excp.what(),MSGLEN);
                strncpy(When,Core::Unknown,MSGLEN);
            }
            catch(...)
            {
                strncpy(What,Core::Unknown,MSGLEN);
                strncpy(When,Core::Unknown,MSGLEN);
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
        static char    What[MSGLEN];
        static char    When[MSGLEN];
    private:
        Y_Disable_Copy_And_Assign(Soak); //!< discarding

    };

    template <typename CLASS> CLASS * Soak<CLASS>:: App = 0;
    template <typename CLASS> char    Soak<CLASS>:: What[];
    template <typename CLASS> char    Soak<CLASS>:: When[];

    //! I/O for dll embedded class
#define Y_Soak(CLASS) \
Y_DLL_SETUP(Yttrium::Soak<CLASS>::Enter,Yttrium::Soak<CLASS>::Leave) Y_DLL_EXTERN()           \
Y_EXPORT bool         Y_DLL_API CLASS##Init() noexcept { return Yttrium::Soak<CLASS>::App;  } \
Y_EXPORT const char * Y_DLL_API CLASS##What() noexcept { return Yttrium::Soak<CLASS>::What; } \
Y_EXPORT const char * Y_DLL_API CLASS##When() noexcept { return Yttrium::Soak<CLASS>::When; } \
Y_DLL_FINISH()
#endif

}



#endif // !Y_RTLD_Soak_Included

