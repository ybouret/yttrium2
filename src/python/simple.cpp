#include "y/rtld/dso.h"
#include <cmath>
#include <iostream>

Y_DLL_EXTERN()

Y_EXPORT double Y_DLL_API sine(double x) noexcept
{
    return sin(x);
}


Y_DLL_FINISH()

static inline void OnEnter(void) {
    std::cerr << "OnEnter" << std::endl;
}

static inline void OnLeave(void)
{
    std::cerr << "OnLeave" << std::endl;
}

Y_DLL_SETUP(OnEnter,OnLeave)

