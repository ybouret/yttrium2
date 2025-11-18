
#include "y/ascii/convert.hpp"
#include "y/exception.hpp"
#include "y/check/usual.hpp"
#include "y/ascii/printable.hpp"

namespace Yttrium
{

    namespace ASCII
    {

        namespace Conversion
        {
            template <>
            apn Parse<apn>(const char * const text,
                           const size_t       size)
            {
                static const uint64_t ten = 10;
                static const char     fn[] = "ASCII<Natural>";
                assert( Good(text,size) );

                if(size<=0) throw Specific::Exception(fn,"empty text");
                apn n;
                for(size_t i=0;i<size;++i)
                {
                    const char c = text[i];
                    switch(c)
                    {
                        case '0':
                        case '1':
                        case '2':
                        case '3':
                        case '4':
                        case '5':
                        case '6':
                        case '7':
                        case '8':
                        case '9':
                            n *= ten;
                            n += uint64_t(c-'0');
                            continue;

                        default:
                            throw Specific::Exception(fn,"invalid char '%s'",Printable::Text(c));
                    }
                }

                return n;
            }
        }

    }

}


