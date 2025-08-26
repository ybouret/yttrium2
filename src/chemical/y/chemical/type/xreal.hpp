
//! \file


#ifndef Y_Chemical_XReal_Included
#define Y_Chemical_XReal_Included 1


#include "y/mkl/xreal.hpp"
#include "y/container/writable.hpp"


namespace Yttrium
{
    namespace Chemical
    {
        typedef double            real_t;    //!< alias
        typedef XReal<double>     xreal_t;   //!< alias
        typedef Readable<xreal_t> XReadable; //!< alias
        typedef Writable<xreal_t> XWritable; //!< alias


    }

}

#endif

