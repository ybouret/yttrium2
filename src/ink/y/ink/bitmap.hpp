//! \file

#ifndef Y_Ink_Bitmap_Included
#define Y_Ink_Bitmap_Included 1

#include "y/object/counted.hpp"

namespace Yttrium
{
    namespace Ink
    {

        class Bitmap 
        {
        public:


            virtual ~Bitmap() noexcept;

        private:
            Y_Disable_Assign(Bitmap);
        };

    }
}

#endif

