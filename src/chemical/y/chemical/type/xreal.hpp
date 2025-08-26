
//! \file


#ifndef Y_Chemical_XReal_Included
#define Y_Chemical_XReal_Included 1


#include "y/mkl/xreal.hpp"
#include "y/container/writable.hpp"


namespace Yttrium
{
    namespace Chemical
    {
        typedef double        real_t;
        typedef XReal<double> xreal_t;

        typedef Readable<xreal_t> XReadable;
        typedef Writable<xreal_t> XWritable;


    }

}

#endif

