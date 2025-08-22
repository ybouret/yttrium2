
//! \file

#ifndef Y_Ink_Pixmap_Included
#define Y_Ink_Pixmap_Included 1

#include "y/ink/bitmap.hpp"
#include "y/memory/operating.hpp"

namespace Yttrium
{
    namespace Ink
    {

        template <typename T>
        class Pixmap : public Bitmap
        {
        public:
            Y_Args_Declare(T,Type);

            class Row
            {
            public:
                Type & operator[](const unit_t i) noexcept
                {
                    return p[ z[i] ];
                }

                ConstType & operator[](const unit_t i) const noexcept
                {
                    return p[ z[i] ];
                }


            private:
                MutableType * const p;
            public:
                const size_t    w;
                const ZeroFlux &z;

            private:
                Row();
                ~Row() noexcept;
                Y_Disable_Copy_And_Assign(Row);
            };

            inline explicit Pixmap(const size_t W, const size_t H) :
            Bitmap(W,H,sizeof(T)),
            ops( data(), items)
            {
            }


            inline virtual ~Pixmap() noexcept
            {
            }



            Row & operator[](const unit_t j) noexcept
            {
                return (Row &)row_[ zflux[j] ];
            }

            const Row & operator[](const unit_t j) const noexcept
            {
                return (const Row &)row_[ zflux[j] ];
            }

        private:
            Y_Disable_Copy_And_Assign(Pixmap);
            Memory::Operating<MutableType> ops;

        };

    }

}

#endif
