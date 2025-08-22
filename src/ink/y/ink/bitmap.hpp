//! \file

#ifndef Y_Ink_Bitmap_Included
#define Y_Ink_Bitmap_Included 1

#include "y/ink/area.hpp"
#include "y/type/copy-of.hpp"

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
            BitRow(void * const, const size_t, const unit_t, const unit_t) noexcept;

        private:
            void * const p; //!< shifted address
        public:
            const size_t w;  //!< width
            const unit_t x;  //!< start coordinante
            const unit_t xt; //!< top coordinate

        private:
            ~BitRow() noexcept;                //!< discarding
            Y_Disable_Copy_And_Assign(BitRow); //!< discarding
        };

        //______________________________________________________________________
        //
        //
        //
        //! Anonymous bitmap with shared content
        //
        //
        //______________________________________________________________________
        class Bitmap : public Area
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definition
            //
            //__________________________________________________________________
            static const char * const CallSign; //!< "Bitmap"
            class Code;
            class Rows;


            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Bitmap(const size_t W,
                            const size_t H,
                            const size_t B);

            explicit Bitmap(const Bitmap &) noexcept;         //!< shared copy
            explicit Bitmap(const CopyOf_ &, const Bitmap &); //!< hard copy


            virtual ~Bitmap() noexcept;


            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            BitRow       & operator()(const unit_t j) noexcept;
            const BitRow & operator()(const unit_t j) const noexcept;


            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const size_t & w;        //!< width.x
            const size_t & h;        //!< width.y
            const size_t   bpp;      //!< bytes per pixels
            const size_t   scanline; //!< bytes per line
            const size_t   stride;   //!< bytes to skip one line
        private:
            Code * const   code; //!< inner code for data
            Rows * const   rows; //!< inner rows memory
        protected:
            BitRow * const row_; //!< row[lower.y:upper.y]

        private:
            Y_Disable_Assign(Bitmap); //!< discarding
            void setup();             //!< setup rows
        };

    }
}

#endif

