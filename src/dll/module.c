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

Y_DLL_SETUP(Enter,Leave)



