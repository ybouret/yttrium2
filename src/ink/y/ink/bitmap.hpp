//! \file

#ifndef Y_Ink_Bitmap_Included
#define Y_Ink_Bitmap_Included 1

#include "y/ink/area.hpp"

namespace Yttrium
{
    namespace Ink
    {


        class Bitmap : public Area
        {
        public:
            static const char * const CallSign;
            
            explicit Bitmap(const size_t W,
                            const size_t H,
                            const size_t B);

            virtual ~Bitmap() noexcept;

            const size_t & w;
            const size_t & h;
            const size_t   bpp;      //!< bytes per pixels
            const size_t   scanline; //!< bytes per line
            const size_t   stride;

        private:
            class Code;
            Y_Disable_Assign(Bitmap);
            Code * const code;

        };

    }
}

#endif

