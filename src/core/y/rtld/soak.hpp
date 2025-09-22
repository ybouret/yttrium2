
//! \file

#ifndef Y_RTLD_Soak_Included
#define Y_RTLD_Soak_Included 1

#include "y/rtld/soak/api.hpp"
#include <cassert>
#include <iostream>

namespace Yttrium
{


    template <typename CLASS>
    class Soak : public SoakAPI
    {
    protected:
        inline explicit Soak() noexcept : SoakAPI() {}

    public:
        inline virtual ~Soak() noexcept {}

        inline virtual const char * callSign() const noexcept { return CLASS::CallSign; }

        static inline void Enter() noexcept
        {
            std::cerr << "<Enter " << CLASS::CallSign << ">" << std::endl;
            assert(0==App);
            try {
                App = new CLASS();
            }
            catch(const Exception &      excp) { OnError(excp); }
            catch(const std::exception & excp) { OnError(excp,CLASS::CallSign); }
            catch(...)                         { OnError(UnhandledException,CLASS::CallSign); }
        }

        static inline void Leave() noexcept
        {
            std::cerr << "<Leave " << CLASS::CallSign << ">" << std::endl;
            if(App) { delete App; App=0; }
        }

        static CLASS * App;
    private:
        Y_Disable_Copy_And_Assign(Soak);
    };

    template <typename CLASS> CLASS * Soak<CLASS>:: App = 0;


#define Y_Soak_Impl(CLASS) \
Y_DLL_SETUP(Yttrium::Soak<CLASS>::Enter,Yttrium::Soak<CLASS>::Leave) Y_DLL_EXTERN()           \
Y_EXPORT bool         Y_DLL_API CLASS##Init() noexcept { return Yttrium::Soak<CLASS>::App;  } \
Y_EXPORT const char * Y_DLL_API CLASS##What() noexcept { return Yttrium::Soak<CLASS>::What; } \
Y_EXPORT const char * Y_DLL_API CLASS##When() noexcept { return Yttrium::Soak<CLASS>::When; } \
Y_DLL_FINISH()

#define Y_Soak_Meth(RETURN,CLASS,METH,ARGS_DECL,ARGS_LIST) \
Y_EXPORT RETURN Y_DLL_API CLASS##METH ARGS_DECL noexcept { return Yttrium::Soak<CLASS>::App->METH ARGS_LIST ;  } \

}



#endif // !Y_RTLD_Soak_Included

