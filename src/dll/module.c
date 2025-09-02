#include "y/rtld/dso.h"

#include <stdio.h>

static inline
void Enter()
{
    printf("Entering !");
}


static inline
void Leave()
{
    printf("Leaving !");
}

Y_DLL_SETUP(Enter,Leave)



