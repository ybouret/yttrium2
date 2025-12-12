
//! \file

#ifndef Y_Fit_Defs_Included
#define Y_Fit_Defs_Included 1


#include "y/mkl/fit/variables.hpp"
#include "y/functor.hpp"

//! return type
#define Y_Fit_Ret_Type ORDINATE

//------------------------------------------------------------------------------
//
// point-wise function/gradient
//
//------------------------------------------------------------------------------

//! arguments for function
#define Y_Fit_Fcn_Args TL4(Readable<ABSCISSA>,size_t,Variables,Readable<ORDINATE>)

//! function prototype
#define Y_Fit_Function Functor<Y_Fit_Ret_Type,Y_Fit_Fcn_Args>

//! arguments for gradient
#define Y_Fit_Grd_Args TL6(Writable<ORDINATE> &,Readable<ABSCISSA>,size_t,Variables,Readable<ORDINATE>,Readable<bool>)

//! prototype for gradient
#define Y_Fit_Gradient Functor<Y_Fit_Ret_Type,Y_Fit_Grd_Args>

//------------------------------------------------------------------------------
//
// usual function/gradient
//
//------------------------------------------------------------------------------
#define Y_Fit_Usual_Fcn_Args TL3(ABSCISSA,Variables,Readable<ORDINATE>)
#define Y_Fit_Usual_Function Functor<Y_Fit_Ret_Type,Y_Fit_Usual_Fcn_Args>



#endif // !Y_Fit_Defs_Included
