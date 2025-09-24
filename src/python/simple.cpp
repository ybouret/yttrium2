#include "y/rtld/dso.h"
#include <cmath>

Y_DLL_EXTERN()

Y_EXPORT double Y_DLL_API sine(double x) noexcept
{
    return sin(x);
}


Y_DLL_FINISH()

static inline void OnEnter(void) {
    
}

static inline void OnLeave(void)
{
}

Y_DLL_SETUP(OnEnter,OnLeave)

