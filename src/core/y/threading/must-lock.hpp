
//! \file

#ifndef Y_Threading_Must_Lock_Included
#define Y_Threading_Must_Lock_Included 1

//! helper to self-lock an object with Threading Policy
#define Y_Must_Lock() volatile Lock guard(*this)


#endif
