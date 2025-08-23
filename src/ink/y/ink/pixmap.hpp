
//! \file

#ifndef Y_Ink_Pixmap_Included
#define Y_Ink_Pixmap_Included 1

#include "y/ink/bitmap.hpp"
#include "y/memory/operating.hpp"
#include "y/core/display.hpp"

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
                inline Type &      operator[](const unit_t i)       noexcept { return p[ z[i] ]; }
                inline ConstType & operator[](const unit_t i) const noexcept { return p[ z[i] ]; }

                inline Type &      operator()(const size_t i)       noexcept { assert(i<w); return p[w]; }
                inline ConstType & operator()(const size_t i) const noexcept { assert(i<w); return p[w]; }

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
            Bitmap(W,H,sizeof(T),Ctor,Dtor)
            {
            }


            //! shared copy
            inline explicit Pixmap(const Pixmap &pxm) noexcept :
            Bitmap(pxm)
            {
            }

            template <typename U> inline
            explicit Pixmap(const CopyOf_ &, const Pixmap<U> &pxm, CTor cpy = Ccpy<U>) :
            Bitmap(CopyOf,pxm,sizeof(T),cpy)
            {
            }

            

            inline virtual ~Pixmap() noexcept
            {
            }

            inline friend std::ostream & operator<<(std::ostream &os, const Pixmap &pxm)
            {
                const size_t jtop = pxm.h-1;
                for(size_t j=0;j<jtop;++j)
                {
                    Core::Display( os, &pxm(j)(0), pxm.w ) << std::endl;
                }

                return  Core::Display( os, &pxm(jtop)(0), pxm.w );
            }

            inline Row & operator[](const unit_t j) noexcept
            {
                return (Row &)row_[ zflux[j] ];
            }

            inline const Row & operator[](const unit_t j) const noexcept
            {
                return (const Row &)row_[ zflux[j] ];
            }

            inline Row & operator()(const size_t j) noexcept
            {
                assert(j<h);
                return (Row &)row_[j];
            }

            inline const Row & operator()(const size_t j) const noexcept
            {
                assert(j<h);
                return (Row &)row_[j];
            }

        private:
            Y_Disable_Assign(Pixmap);
            static inline void Ctor(void * const addr, const void * const)
            {
                assert(addr); new (addr) MutableType();
            }

            static inline void Dtor(void * const addr) noexcept
            {
                assert(addr); static_cast<MutableType *>(addr)->~MutableType();
            }

        public:
            template <typename U> static inline
            void Ccpy(void * const addr, const void * const args)
            {
                assert(addr); assert(args);
                typedef typename TypeTraits<U>::MutableType UU;
                new (addr) MutableType( *static_cast<const UU *>(args) );
            }


        };

    }

}

#endif
