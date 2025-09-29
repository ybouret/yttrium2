
//! \file

#ifndef Y_RTLD_Spyndle_Included
#define Y_RTLD_Spyndle_Included 1

#include "y/rtld/spyndle/api.hpp"

namespace Yttrium
{

    template <typename T>
    class Spyndle : public SpyndleAPI
    {
    public:
        typedef T ClassType;
        static  T * App;


        inline virtual const char * callSign() const noexcept
        {
            return ClassType:: CallSign;
        }


        static inline bool Init() noexcept
        {
            assert(0==App);
            Y_Spyndle_Code(App = new ClassType(),return true,return false);
        }

        static inline void Quit() noexcept
        {
            if(App) { delete App; App=0; }
        }

        inline virtual ~Spyndle() noexcept
        {

        }

    protected:
        inline explicit Spyndle() noexcept : SpyndleAPI()
        {
        }

    private:
        Y_Disable_Copy_And_Assign(Spyndle);

    };

    template <typename T> T * Spyndle<T>:: App = 0;

}

#define Y_Spyndle(CLASS) \
Y_DLL_EXTERN() \
Y_EXPORT const char * Y_DLL_API CLASS##_What() noexcept { return CLASS::What;   } \
Y_EXPORT const char * Y_DLL_API CLASS##_When() noexcept { return CLASS::When;   } \
Y_EXPORT bool         Y_DLL_API CLASS##_Init() noexcept { return CLASS::Init(); } \
Y_EXPORT void         Y_DLL_API CLASS##_Quit() noexcept { CLASS::Quit();        } \
Y_DLL_FINISH()


#define Y_Spyndle_Meth(RETURN,CLASS,METH,ARGS_DECL,ARGS_LIST) \
Y_DLL_CPROTO Y_EXPORT RETURN Y_DLL_API CLASS##_##METH ARGS_DECL noexcept { return Yttrium::Spyndle<CLASS>::App->METH ARGS_LIST ;  } \


#endif // !Y_RTLD_Spyndle_Included

