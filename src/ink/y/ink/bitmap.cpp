
#include "y/ink/bitmap.hpp"
#include "y/exception.hpp"
#include "y/object/counted.hpp"
#include "y/object/school-of.hpp"
#include "y/type/destroy.hpp"

namespace Yttrium
{
    namespace Ink
    {
        const char * const Bitmap:: CallSign = "Bitmap";


        namespace
        {
            typedef Memory::SchoolOf<uint8_t> BitmapData;
            typedef Memory::SchoolOf<BitRow>  BitmapRows;
        }

        class Bitmap:: Code : public CountedObject

        {
        protected:
            //! initialize, on and off can be NULL
            inline explicit Code(const size_t   bpp,
                                 Bitmap::CTor   on,
                                 Bitmap::DTor   off) noexcept :
            CountedObject(), bsize(bpp), ctor(on), dtor(off)
            {}

        public:
            //! cleanup
            inline virtual  ~Code() noexcept {}

            //! access data
            virtual uint8_t * get() const noexcept = 0;

            const size_t bsize; //!< block size
            Bitmap::CTor ctor;  //!< constructor if needed
            Bitmap::DTor dtor;  //!< destructor  if needed

        private:
            Y_Disable_Copy_And_Assign(Code);
        };

        namespace
        {
            class MemCode : public Bitmap::Code, public BitmapData
            {
            public:
                inline explicit MemCode(const size_t items,
                                        const size_t bpp,
                                        Bitmap::CTor on,
                                        Bitmap::DTor off) :
                Bitmap::Code(bpp,on,off),
                BitmapData(items*bpp),
                built(0)
                {
                    assert(ctor); assert(dtor);
                    init(items);
                }

                inline explicit MemCode(const Code    &code,
                                        const size_t   items,
                                        const size_t   bpp,
                                        Bitmap::CTor   cpy) :
                Bitmap::Code(bpp,cpy,code.dtor),
                BitmapData(items*bsize),
                built(0)
                {
                    assert(ctor); assert(dtor);
                    init(items,code.get(),code.bsize);
                }

                inline virtual ~MemCode() noexcept { quit(); }

                inline virtual uint8_t * get() const noexcept { return entry; }

            private:
                Y_Disable_Copy_And_Assign(MemCode);
                size_t       built;

                inline void init(const size_t items)
                {

                    try {
                        uint8_t *ptr = entry;
                        while(built<items)
                        {
                            ctor(ptr,0);
                            ptr+=bsize;
                            ++built;
                        }
                    }
                    catch(...) { quit(); throw; }
                }

                inline void init(const size_t    items,
                                 const uint8_t * src,
                                 const size_t    sbs)
                {
                    try {

                        uint8_t *       tgt = entry;
                        const size_t    tbs = bsize;
                        while(built<items)
                        {
                            ctor(tgt,src);
                            tgt+=tbs;
                            src+=sbs;
                            ++built;
                        }
                    }
                    catch(...) { quit(); throw; }
                }


                inline void  quit() noexcept
                {
                    uint8_t *ptr = entry + (built*bsize);
                    while(built-- > 0)
                    {
                        dtor( ptr -= bsize );
                    }
                }
            };
        }


      

        class Bitmap:: Rows : public BitmapRows
        {
        public:

            inline explicit Rows(const Bitmap & bmp,
                                 uint8_t *      ptr) :
            BitmapRows(bmp.h),
            z(bmp.w)
            {
                for(size_t j=0;j<bmp.h;++j, ptr += bmp.stride)
                {
                    new (entry+j) BitRow(ptr,bmp.w,z);
                }
            }


            inline virtual ~Rows() noexcept {}

            const ZeroFlux z;

        private:
            Y_Disable_Copy_And_Assign(Rows);

        };

        Bitmap:: ~Bitmap() noexcept
        {
            assert(code);
            assert(rows);
            if(rows->liberate()) Destroy(rows);
            if(code->liberate()) Destroy(code);
        }

        namespace
        {
            static inline
            unit_t GetUnit(const char * const id, const size_t n)
            {
                assert(id);
                if(n<=0) throw Specific::Exception(Bitmap::CallSign,"zero %s", id);
                return (unit_t)(n-1);
            }

            static inline
            Point GetCoord(const size_t W, const size_t H)
            {
                const unit_t x = GetUnit("width",W);
                const unit_t y = GetUnit("height",H);
                return Point(x,y);
            }

            static inline size_t CheckBPP(const size_t B)
            {
                if(B<=0) throw Specific::Exception(Bitmap::CallSign,"no bytes per pixels");
                return B;
            }

        }

        void Bitmap:: setup()
        {
            try {
                Coerce(rows) = new Rows(*this,code->get());
                Coerce(row_) = rows->entry;
                code->withhold();
                rows->withhold();
            }
            catch(...)
            {
                Destroy(code); throw;
            }
        }

        Bitmap:: Bitmap(const size_t W,
                        const size_t H,
                        const size_t B,
                        CTor         ctor,
                        DTor         dtor) :
        Area( Point(0,0), GetCoord(W,H) ),
        w(width.x),
        h(width.y),
        bpp( CheckBPP(B) ),
        scanline( w * bpp ),
        stride( scanline  ),
        zflux(h),
        code( new MemCode(items,bpp,ctor,dtor) ),
        rows( 0 ),
        row_( 0 )
        {
            setup();
        }


        BitRow & Bitmap:: getRow(const size_t j) noexcept
        {
            assert(j<w);
            return row_[j];
        }

        const BitRow & Bitmap:: getRow(const size_t j) const noexcept
        {
            assert(j<w);
            return row_[j];
        }


        Bitmap:: Bitmap(const Bitmap &bmp) noexcept :
        Area(bmp),
        w(width.x),
        h(width.y),
        bpp(bmp.bpp),
        scanline( bmp.scanline ),
        stride(   bmp.stride   ),
        zflux(    bmp.zflux    ),
        code(     bmp.code     ),
        rows(     bmp.rows     ),
        row_(     bmp.row_     )
        {
            code->withhold();
            rows->withhold();
            assert(h==bmp.h);
            assert(w==bmp.w);
        }


        Bitmap:: Bitmap(const CopyOf_&,
                        const Bitmap &bmp,
                        const size_t  B,
                        CTor          cpy) :
        Area(bmp),
        w(width.x),
        h(width.y),
        bpp(B),
        scanline( w*bpp     ),
        stride(   scanline  ),
        zflux(    bmp.zflux ),
        code( new MemCode(*bmp.code,items,bpp,cpy) ),
        rows( 0 ),
        row_( 0 )
        {
            setup();
            assert(h==bmp.h);
            assert(w==bmp.w);
        }


        void * Bitmap:: data() noexcept
        {
            assert( code );
            return code->get();
        }
    }

}

