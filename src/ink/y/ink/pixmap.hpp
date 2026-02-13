
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

        //______________________________________________________________________
        //
        //
        //
        //! Bitmap of pixels
        //
        //
        //______________________________________________________________________
        template <typename T>
        class Pixmap : public Bitmap
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            Y_Args_Declare(T,Type); //!< alias


            //__________________________________________________________________
            //
            //! aliased row
            //__________________________________________________________________
            class Row
            {
            public:
                inline Type &      operator[](const unit_t i)       noexcept { return p[ z[i] ]; } //!< \param i position \return safe value
                inline ConstType & operator[](const unit_t i) const noexcept { return p[ z[i] ]; } //!< \param i position \return safe value

                inline Type &      operator()(const size_t i)       noexcept { assert(i<w); return p[i]; } //!< \param i index \return value
                inline ConstType & operator()(const size_t i) const noexcept { assert(i<w); return p[i]; } //!< \param i index \return value

            private:
                MutableType * const p; //!< first item address
            public:
                const size_t    w;     //!< width
                const ZeroFlux &z;     //!< shared ZeroFlux(w)

            private:
                Row();                          //!< discard
                ~Row() noexcept;                //!< discard
                Y_Disable_Copy_And_Assign(Row); //!< discard
            };

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup \param W width \param H height
            inline explicit Pixmap(const size_t W, const size_t H) :
            Bitmap(W,H,sizeof(T),Ctor,Dtor)
            {
            }


            //! shared copy \param pxm source pixmap
            inline Pixmap(const Pixmap &pxm) noexcept :
            Bitmap(pxm)
            {
            }

            //! hard copy with possible transmogrification
            /**
             \param pxm source pixmap
             \param cpy pixel-wise copy constructor
             */
            template <typename U> inline
            explicit Pixmap(const CopyOf_ &, const Pixmap<U> &pxm, CTor cpy = Ccpy<U>) :
            Bitmap(CopyOf,pxm,sizeof(T),cpy)
            {
                assert(h==pxm.h);
                assert(w==pxm.w);
            }


            //! cleanup
            inline virtual ~Pixmap() noexcept
            {
            }

            //! display as rows of vectors
            inline friend std::ostream & operator<<(std::ostream &os, const Pixmap &pxm)
            {
                const size_t jtop = pxm.h-1;
                for(size_t j=0;j<jtop;++j)
                {
                    Core::Display( os, &pxm(j)(0), pxm.w ) << std::endl;
                }
                return  Core::Display( os, &pxm(jtop)(0), pxm.w );
            }

            //! \param j position \return safe row
            inline Row & operator[](const unit_t j) noexcept
            {
                return (Row &)row_[ zflux[j] ];
            }

            //! \param j position \return safe row
            inline const Row & operator[](const unit_t j) const noexcept
            {
                return (const Row &)row_[ zflux[j] ];
            }

            //! \param j index \return row[j]
            inline Row & operator()(const size_t j) noexcept
            {
                assert(j<h);
                return (Row &)row_[j];
            }

            //! \param j index \return row[j]
            inline const Row & operator()(const size_t j) const noexcept
            {
                assert(j<h);
                return (const Row &)row_[j];
            }

            inline Type & operator[](const Point p) noexcept
            {
                return (*this)[p.y][p.x];
            }

            inline ConstType & operator[](const Point p) const noexcept
            {
                return (*this)[p.y][p.x];
            }

            inline friend bool operator==(const Pixmap &lhs, const Pixmap &rhs)
            {
                {
                    const Area &la = lhs;
                    const Area &ra = rhs;
                    //std::cerr << "lhs.area=" << la << " / rhs.area=" << ra << std::endl;
                    if(la!=ra)
                        return false;
                    // std::cerr << "width: " << la.width << " / " << ra.width << std::endl;
                    // std::cerr << "h=" << lhs.h << " / " << rhs.h << std::endl;
                    // std::cerr << "w=" << lhs.w << " / " << rhs.w << std::endl;
                }

                assert(lhs.h==rhs.h);
                assert(lhs.w==rhs.w);

                for(size_t j=0;j<lhs.h;++j)
                {
                    const Row &l = lhs(j);
                    const Row &r = rhs(j);
                    for(size_t i=0;i<lhs.w;++i)
                    {
                        if( l(i) != r(i) ) return false;
                    }
                }
                return true;
            }

        private:
            Y_Disable_Assign(Pixmap); //!< discarding

            //! default constructor \param addr where to build pixel
            static inline void Ctor(void * const addr, const void * const)
            {
                assert(addr); new (addr) MutableType();
            }

            //! default destructor \param addr pixel address
            static inline void Dtor(void * const addr) noexcept
            {
                assert(addr); static_cast<MutableType *>(addr)->~MutableType();
            }

        public:

            //! flexible constructor
            /**
             \param addr address of T
             \param args address of U
             */
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

#endif // !Y_Ink_Pixmap_Included
