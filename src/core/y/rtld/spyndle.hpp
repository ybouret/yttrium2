
//! \file

#ifndef Y_RTLD_Spyndle_Included
#define Y_RTLD_Spyndle_Included 1

#include "y/rtld/spyndle/api.hpp"

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //! Application in one DLL
    //
    //
    //__________________________________________________________________________
    template <typename T>
    class Spyndle : public SpyndleAPI
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        typedef T ClassType; //!< alias
        static  T * App;     //!< 'singleton' app


        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________
        inline virtual const char * callSign() const noexcept
        {
            return ClassType:: CallSign;
        }

        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________

        //! create application \return true iff succcess
        static inline bool Init() noexcept
        {
            reset();
            Y_Spyndle_Boolean(App = new ClassType());
        }

        //! delete existing application
        static inline void Quit() noexcept
        {
            reset();
        }

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
        inline virtual ~Spyndle() noexcept {} //!< cleanup
    protected:
        inline explicit Spyndle() noexcept : SpyndleAPI() {} //!< setup

    private:
        Y_Disable_Copy_And_Assign(Spyndle); //!< discarding
        static inline void reset() noexcept
        {
            if(App) { delete App; App=0; }
        }
    };

    template <typename T> T * Spyndle<T>:: App = 0; //!< alias

}

//! define What/When/Init and Quit method for global management
#define Y_Spyndle(CLASS) \
Y_DLL_EXTERN() \
Y_EXPORT const char * Y_DLL_API CLASS##_What() noexcept { return CLASS::What;   } \
Y_EXPORT const char * Y_DLL_API CLASS##_When() noexcept { return CLASS::When;   } \
Y_EXPORT bool         Y_DLL_API CLASS##_Init() noexcept { return CLASS::Init(); } \
Y_EXPORT void         Y_DLL_API CLASS##_Quit() noexcept { CLASS::Quit();        } \
Y_DLL_FINISH()

//! helper to call a method thru a C-function
#define Y_Spyndle_Meth(RETURN,CLASS,METH,ARGS_DECL,ARGS_LIST) \
Y_DLL_CPROTO Y_EXPORT RETURN Y_DLL_API CLASS##_##METH ARGS_DECL noexcept { return Yttrium::Spyndle<CLASS>::App->METH ARGS_LIST ;  } \


#endif // !Y_RTLD_Spyndle_Included

