#include "y/core/text.hpp"
#include "y/check/usual.hpp"
#include "y/core/utils.hpp"
#include <cstring>

namespace Yttrium
{
    namespace Core
    {
        size_t Text:: Length(const char * const text) noexcept
        {
            return 0 != text ? strlen(text) : 0;
        }


        char * Text:: Copy(char * const       outputBuffer,
                           const size_t       outputLength,
                           const char * const text) noexcept
        {
            assert( Good(outputBuffer,outputLength) );
            if(outputLength>0)
            {
                const size_t textLength  = Length(text);
                const size_t copyLength  = outputLength-1;
                const size_t length      = MinOf(textLength,copyLength);
                memcpy(outputBuffer,text,length);
                memset(outputBuffer+length,0,outputLength-length);
            }
            return outputBuffer;
        }
    }

}
