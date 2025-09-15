#include "y/rtld/soak.hpp"
#include "y/string.hpp"

#include <iostream>
#include <cmath>

using namespace Yttrium;

class Application
{
public:
    explicit Application() : name("TheApplication")
    {
        std::cerr << "Created " << name << std::endl;
    }

    virtual ~Application() noexcept
    {
        std::cerr << "Deleted " << name << std::endl;
    }

    const String name;
private:
    Y_Disable_Copy_And_Assign(Application);
};


Y_Soak(Application);

#if 0
static inline
void Enter() noexcept
{
    std::cerr << "[Enter++]" << std::endl;
}


static inline
void Leave()
{
    std::cerr << "[Leave++]" << std::endl;
}
#endif


Y_DLL_EXTERN()

Y_EXPORT double Y_DLL_API sine(double x) noexcept
{
    return sin(x);
}


Y_DLL_FINISH()

//Y_DLL_SETUP(Enter,Leave)


