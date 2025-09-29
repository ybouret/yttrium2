
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


        inline virtual const char * callSign() const noexcept
        {
            return ClassType:: CallSign;
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

}

#define Y_Spyndle(CLASS) \
Y_DLL_EXTERN() \
Y_EXPORT const char * Y_DLL_API CLASS_What() noexcept { return CLASS::What; } \
Y_EXPORT const char * Y_DLL_API CLASS_When() noexcept { return CLASS::When; } \
Y_DLL_FINISH()

#endif // !Y_RTLD_Spyndle_Included

