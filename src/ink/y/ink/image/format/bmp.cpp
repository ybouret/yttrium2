
#include "y/ink/image/format/bmp.hpp"

namespace Yttrium
{
    namespace Ink
    {

        const char * const FormatBMP:: CallSign  = "BMP";
        const char * const FormatBMP:: Extension = "bmp";


        FormatBMP:: FormatBMP() :
        Format(CallSign,Extension)
        {
        }
        
        FormatBMP:: ~FormatBMP() noexcept {}


        void FormatBMP::save(const Image &img, const String &fileName)
        {
            
        }
    }

}
