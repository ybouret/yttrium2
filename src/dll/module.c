#include "y/rtld/dso.h"

#include <stdio.h>
#include <math.h>

static inline
void Enter()
{
    printf("Enter !\n");
}


static inline
void Leave()
{
    printf("Leave !\n");
}

Y_DLL_EXTERN()

Y_EXPORT double Y_DLL_API Sine(double x)
{
    return sin(x);
}

Y_DLL_FINISH()

Y_DLL_SETUP(Enter,Leave)



