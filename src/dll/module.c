#include "y/rtld/dso.h"

#include <stdio.h>
#include <math.h>

static
void Enter(void)
{
    printf("Enter !\n");
}

static 
void Leave(void)
{
    printf("Leave !\n");
}

Y_DLL_EXTERN()

Y_EXPORT double Y_DLL_API Sine(double x)
{
    return sin(x);
}

Y_EXPORT uint32_t Data[4] = { 0x1, 0x2, 0x3, 0x4 };



Y_DLL_FINISH()

Y_DLL_SETUP(Enter,Leave)



