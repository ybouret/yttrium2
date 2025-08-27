
//! \file


#ifndef Y_Chemical_XReal_Included
#define Y_Chemical_XReal_Included 1


#include "y/mkl/xreal.hpp"
#include "y/container/cxx/array.hpp"
#include "y/cameo/addition.hpp"
#include "y/cameo/multiplication.hpp"


namespace Yttrium
{
    namespace Chemical
    {
        typedef double            real_t;    //!< alias
        typedef XReal<double>     xreal_t;   //!< alias
        typedef Readable<xreal_t> XReadable; //!< alias
        typedef Writable<xreal_t> XWritable; //!< alias

        typedef CxxArray<xreal_t> XArray;

        typedef Cameo::Multiplication<xreal_t> XMul;
        typedef Cameo::Addition<xreal_t>       XAdd;

    }

}

#endif

