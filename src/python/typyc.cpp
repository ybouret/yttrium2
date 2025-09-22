#include "y/rtld/soak.hpp"
#include "y/string.hpp"

#include <iostream>
#include <cmath>

using namespace Yttrium;

class Application : public Soak<Application>
{
public:
    static const char * const CallSign;

    

private:
    Y_Disable_Copy_And_Assign(Application);
    friend class Soak<Application>;

    explicit Application() noexcept;
    virtual ~Application() noexcept;

};

Application:: Application() noexcept : Soak<Application>()
{
}

Application:: ~Application() noexcept
{
}


const char * const Application :: CallSign = "Application";

Y_Soak_Impl(Application)


Y_DLL_EXTERN()

Y_EXPORT double Y_DLL_API sine(double x) noexcept
{
    return sin(x);
}

Y_DLL_FINISH()



