//! \file

#ifndef Y_Ink_Bitmap_Included
#define Y_Ink_Bitmap_Included 1

#include "y/ink/area.hpp"
#include "y/type/copy-of.hpp"
#include "y/ink/bitrow.hpp"

namespace Yttrium
{
    namespace Ink
    {

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
            // Definitions
            //
            //__________________________________________________________________
            static const char * const CallSign;                     //!< "Bitmap"
            typedef void (*CTor)(void * const, const void * const); //!< constructor prototype
            typedef void (*DTor)(void * const);                     //!< destructor prototupe
            class Code;
            class Rows;


            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! full setup
            /**
             \param W width
             \param H height
             \param D depth
             \param ctor ctor(addr,NULL) to construct
             \param dtor dtor(addr)      to destruct
             */
            explicit Bitmap(const size_t W,
                            const size_t H,
                            const size_t D,
                            CTor         ctor,
                            DTor         dtor);

            //! noexcept shared copy
            explicit Bitmap(const Bitmap &) noexcept;

            //! copy
            /**
             \param bmp  original bitmap
             \param D    this depth
             \param cpy  cpy(bmp.item,item) with possible different types
             */
            explicit Bitmap(const CopyOf_ &,
                            const Bitmap  & bmp,
                            const size_t    D,
                            CTor            cpy); //!< hard copy

            //! cleanup
            virtual ~Bitmap() noexcept;


            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            BitRow       & getRow(const size_t)       noexcept; //!< \return direct row access
            const BitRow & getRow(const size_t) const noexcept; //!< \return direct row access


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
            const ZeroFlux zflux;    //!< ZeroFlux(h)

        private:
            Code * const   code; //!< inner code for data
            Rows * const   rows; //!< inner rows memory
        protected:
            BitRow * const row_; //!< row[0:w-1]
            void *         data() noexcept; //!< \return first data byte a.k.a &row[0][0]

        private:
            Y_Disable_Assign(Bitmap); //!< discarding
            void setup();             //!< setup rows
        };

    }
}

#endif

