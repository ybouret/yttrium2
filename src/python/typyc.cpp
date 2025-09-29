#include "y/rtld/soak.hpp"
#include "y/string.hpp"
#include "y/mkl/api/pythagoras.hpp"
#include <iostream>
#include <cmath>

using namespace Yttrium;

class Application : public Soak<Application>
{
public:
    static const char * const CallSign;

    inline double Norm(const double x, const double y)
    {
        return MKL::Pythagoras(x,y);
    }

private:
    Y_Disable_Copy_And_Assign(Application);
    friend class Soak<Application>;

    explicit Application() noexcept;
    virtual ~Application() noexcept;

};

Application:: Application() noexcept : Soak<Application>()
{
    std::cerr << "[+] Application" << std::endl;
}

Application:: ~Application() noexcept
{
    std::cerr << "[-] Application" << std::endl;
}



const char * const Application :: CallSign = "Application";

//Y_Soak_Impl(Application)


// some C functions

Y_DLL_EXTERN()

Y_EXPORT double Y_DLL_API sine(double x) noexcept
{
    return sin(x);
}

Y_DLL_FINISH()

Y_Soak_Meth(double,Application,Norm,(double x, double y),(x,y))


