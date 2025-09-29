#include "y/rtld/spyndle.hpp"
#include "y/concurrent/singulet.hpp"
#include "y/string.hpp"
#include "y/mkl/api/pythagoras.hpp"

#include <cmath>
#include <iostream>
#include <cassert>

using namespace Yttrium;


class Application : public Spyndle<Application>
{
public:
    static const char * const CallSign;

    explicit Application()
    {
    }

    virtual ~Application() noexcept
    {

    }

    inline double norm(const double x, const double y)
    {
        return MKL::Pythagoras(x,y);
    }


private:
    Y_Disable_Copy_And_Assign(Application);
};


const char * const Application:: CallSign = "Application";

Y_Spyndle(Application)

Y_Spyndle_Meth(double,Application,norm,(double x, double y), (x,y) )
 

Y_DLL_EXTERN()

Y_EXPORT double Y_DLL_API sine(double x) noexcept
{
    return sin(x);
}

Y_DLL_FINISH()




