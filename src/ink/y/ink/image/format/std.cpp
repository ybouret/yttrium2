
#include "y/ink/image/formats.hpp"
#include "y/ink/image/format/png.hpp"
#include "y/ink/image/format/jpeg.hpp"
#include "y/ink/image/format/tiff.hpp"
#include "y/ink/image/format/pnm.hpp"

namespace Yttrium
{
    namespace Ink
    {

        template <typename FMT> static inline
        void ensureLoaded( Formats &db )
        {
            const String key = FMT::CallSign; if(db.search(key)) return;
            db( new FMT() );
        }

        void Formats:: loadBuiltIn()
        {
            ensureLoaded<FormatPNG>(*this);
            ensureLoaded<FormatJPEG>(*this);
            ensureLoaded<FormatTIFF>(*this);
            ensureLoaded<FormatPNM>(*this);
        }

        Formats & Formats:: Std()
        {
            static Formats &db = Instance();
            db.loadBuiltIn();
            return db;
        }
    }

}
