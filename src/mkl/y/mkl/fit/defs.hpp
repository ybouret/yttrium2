
//! \file

#ifndef Y_Fit_Defs_Included
#define Y_Fit_Defs_Included 1


#include "y/mkl/fit/variables.hpp"
#include "y/functor.hpp"

#define Y_Fit_Ret_Type ORDINATE
#define Y_Fit_Fcn_Args TL4(Readable<ABSCISSA>,size_t,Variables,Readable<ORDINATE>)
#define Y_Fit_Functor  Functor<Y_Fit_Ret_Type,Y_Fit_Fcn_Args>

#endif // !Y_Fit_Defs_Included
