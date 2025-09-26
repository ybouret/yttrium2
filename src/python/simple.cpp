#include "y/rtld/dso.h"
#include "y/concurrent/singulet.hpp"
#include "y/string.hpp"

#include <cmath>
#include <iostream>
#include <cassert>

using namespace Yttrium;

class Simple : public Object
{
public:
    explicit Simple() : name("Simple")
    {
    }

    virtual ~Simple() noexcept
    {
    }

    const String name;

    static Simple *App;

    static bool Init()
    {
        assert(0==App);
        Concurrent::Singulet::Verbose = true;
        App = new Simple();
        return true;
    }

    static void Quit() noexcept
    {
        if(App) { delete App; App = 0; }
    }

private:
    Y_Disable_Copy_And_Assign(Simple);
};

Simple * Simple::App = 0;


Y_DLL_EXTERN()

Y_EXPORT double Y_DLL_API sine(double x) noexcept
{
    return sin(x);
}

Y_EXPORT bool Y_DLL_API Simple_Init() noexcept
{
    return Simple::Init();
}

Y_EXPORT void Y_DLL_API Simple_Quit() noexcept
{
    Simple::Quit();
}

Y_DLL_FINISH()


