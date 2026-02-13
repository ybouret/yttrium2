

//! \file

#ifndef Y_Container_Algo_Crop_Included
#define Y_Container_Algo_Crop_Included 1

#include "y/container/algorithm/trim.hpp"
#include "y/container/algorithm/skip.hpp"

namespace Yttrium
{
    namespace Algo
    {
        //______________________________________________________________________
        //
        //
        //! Trim last bad items
        /**
         \param seq sequence-like container
         \param bad return true iif bad
         \return cropped seq
         */
        //
        //______________________________________________________________________
        template <typename SEQUENCE, typename IS_BAD>
        inline SEQUENCE &Crop(SEQUENCE &seq, IS_BAD &bad)
        {
            return Skip(Trim(seq,bad),bad);
        }
    }

}
#endif // !Y_Container_Algo_Crop_Included

