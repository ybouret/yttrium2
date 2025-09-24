//! \file

#ifndef Y_MKL_ODE_Field_Included
#define Y_MKL_ODE_Field_Included 1

#include "y/container/writable.hpp"
#include "y/functor.hpp"

namespace Yttrium
{
    namespace MKL
    {
        namespace ODE
        {

            //__________________________________________________________________
            //
            //
            //
            //! Definitions
            //
            //
            //__________________________________________________________________
            template <typename T>
            struct Field
            {

                typedef Functor<void,TL3(Writable<T> &,T,const Readable<T>)> Equation; //!< alias
                typedef Functor<void,TL2(Writable<T> &,T)>                   Callback; //!< alias
            };

        }
    }

}


#endif // !Y_MKL_ODE_Field_Included
