
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
        }

        class Bitmap:: Code : public CountedObject, public BitmapData

        {
        public:
            explicit Code(const size_t items) :
            CountedObject(),
            BitmapData(items)
            {

            }

            virtual ~Code() noexcept
            {

            }

        private:
            Y_Disable_Copy_And_Assign(Code);
        };

        Bitmap:: ~Bitmap() noexcept
        {
            assert(code);
            Destroy(code);
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

        Bitmap:: Bitmap(const size_t W,
                        const size_t H,
                        const size_t B) :
        Area( Coord(0,0), GetCoord(W,H) ),
        w(width.x),
        h(width.y),
        bpp( CheckBPP(B) ),
        scanline( w * bpp ),
        stride( scanline  ),
        code( new Code(items) )
        {

        }
    }

}

