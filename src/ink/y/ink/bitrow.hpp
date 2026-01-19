
//! \file

#ifndef Y_Ink_Bitrow_Included
#define Y_Ink_Bitrow_Included 1

#include "y/ink/zero-flux.hpp"

namespace Yttrium
{
    namespace Ink
    {
        //______________________________________________________________________
        //
        //
        //
        //! anonymous bit-row
        //
        //
        //______________________________________________________________________
        class BitRow
        {
        public:

            //! setup by Bitmap
            BitRow(void * const,
                   const size_t,
                   const ZeroFlux &) noexcept;

        private:
            void * const    p; //!< shifted address
        public:
            const size_t    w;  //!< width
            const ZeroFlux &z;  //!< ZeroFlux(w)
            
        private:
            ~BitRow() noexcept;                //!< discarding
            Y_Disable_Copy_And_Assign(BitRow); //!< discarding
        };

    }

}

#endif // !Y_Ink_Bitrow_Included

