

#include "y/ascii/convert.hpp"
#include "y/system/exception.hpp"
#include "y/check/usual.hpp"

namespace Yttrium
{

    namespace ASCII
    {

        namespace Conversion
        {
            template <>
            apz Parse<apz>(const char * const text,
                           const size_t       size)
            {
                static const int64_t  ten = 10;
                static const char     fn[] = "ASCII<Integer>";
                assert( Good(text,size) );

                if(size<=0) throw Specific::Exception(fn,"empty text");
                bool   neg = false;
                size_t i0  = 0;

                if('-'==text[0])
                {
                    if(1==size) throw Specific::Exception(fn,"single '-'");
                    neg = true;
                    i0  = 1;
                }

                if('+'==text[0])
                {
                    if(1==size) throw Specific::Exception(fn,"single '+'");
                    i0  = 1;
                }

                apz  z;
                for(size_t i=i0;i<size;++i)
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
                            z *= ten;
                            z += int64_t(c-'0');
                            continue;
                        default:
                            throw Specific::Exception(fn,"invalid char '%c'",c);
                    }
                }

                return neg ? -z : z;
            }
        }

    }

}


