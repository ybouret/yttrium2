//! \file

#ifndef Y_Ink_Bitmap_Included
#define Y_Ink_Bitmap_Included 1

#include "y/ink/area.hpp"

namespace Yttrium
{
    namespace Ink
    {


        class BitRow
        {
        public:
            BitRow(uint8_t * const, const size_t, const unit_t, const unit_t) noexcept;

        private:
            uint8_t * const p;
        public:
            const size_t w;
            const unit_t x;
            const unit_t xt;

        private:
            Y_Disable_Copy_And_Assign(BitRow);
        };

        class Bitmap : public Area
        {
        public:
            static const char * const CallSign;
            class Code;

            explicit Bitmap(const size_t W,
                            const size_t H,
                            const size_t B);

            virtual ~Bitmap() noexcept;

            BitRow       & operator()(const unit_t j) noexcept;
            const BitRow & operator()(const unit_t j) const noexcept;

            const size_t & w;
            const size_t & h;
            const size_t   bpp;      //!< bytes per pixels
            const size_t   scanline; //!< bytes per line
            const size_t   stride;

        private:
            class Rows;
            Y_Disable_Copy_And_Assign(Bitmap);
            Code * const   code;
            Rows * const   rows;
        protected:
            BitRow * const row_;
        };

    }
}

#endif

