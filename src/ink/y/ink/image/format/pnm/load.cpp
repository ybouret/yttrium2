
#include "y/ink/image/format/pnm.hpp"
#include "y/system/exception.hpp"

namespace Yttrium
{
    namespace Ink
    {
        
        Image FormatPNM:: load(const String &fileName,
                                      const Options * ) const
        {
            throw Specific::Exception(CallSign,"load is not implemented yet for '%s'", fileName.c_str());
            return Image(1,1);
        }
    }
    
}
