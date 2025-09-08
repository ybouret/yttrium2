#include "y/rtld/dso.h"

#include <iostream>
#include <cmath>

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

Y_DLL_EXTERN()

Y_EXPORT double Y_DLL_API sine(double x) noexcept
{
    return sin(x);
}


Y_DLL_FINISH()

Y_DLL_SETUP(Enter,Leave)



