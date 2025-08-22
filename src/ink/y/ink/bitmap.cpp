
#include "y/ink/bitmap.hpp"
#include "y/system/exception.hpp"
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
        public:
            inline explicit Code() noexcept : CountedObject() {}
            inline virtual ~Code() noexcept {}

            virtual uint8_t * get() const noexcept = 0;

        private:
            Y_Disable_Copy_And_Assign(Code);
        };

        namespace
        {
            class MemCode : public Bitmap::Code, public BitmapData
            {
            public:
                inline explicit MemCode(const size_t total) : Bitmap::Code(), BitmapData(total) { }
                inline virtual ~MemCode() noexcept {}

                inline virtual uint8_t * get() const noexcept { return entry; }

            private:
                Y_Disable_Copy_And_Assign(MemCode);
            };
        }


      

        class Bitmap:: Rows : public CountedObject, public BitmapRows
        {
        public:

            inline explicit Rows(const Bitmap & bmp,
                                 uint8_t *      ptr) :
            CountedObject(),
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
            Coord GetCoord(const size_t W, const size_t H)
            {
                const unit_t x = GetUnit("width",W);
                const unit_t y = GetUnit("height",H);
                return Coord(x,y);
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
                Coerce(row_) = rows->entry - lower.y;
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
                        const size_t B) :
        Area( Coord(0,0), GetCoord(W,H) ),
        w(width.x),
        h(width.y),
        bpp( CheckBPP(B) ),
        scanline( w * bpp ),
        stride( scanline  ),
        zflux(h),
        code( new MemCode(items*bpp) ),
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
        code( bmp.code ),
        rows( bmp.rows ),
        row_( bmp.row_ )
        {
            code->withhold();
            rows->withhold();
        }


        Bitmap:: Bitmap(const CopyOf_&, const Bitmap &bmp) :
        Area(bmp),
        w(width.x),
        h(width.y),
        bpp(bmp.bpp),
        scanline( bmp.scanline ),
        stride(   bmp.stride   ),
        zflux(    bmp.zflux    ),
        code( new MemCode(items*bpp) ),
        rows( 0 ),
        row_( 0 )
        {
            setup();
        }


        void * Bitmap:: data() noexcept
        {
            assert( code );
            return code->get();
        }
    }

}

