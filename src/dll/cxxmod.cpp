
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

Y_DLL_SETUP(Enter,Leave)



