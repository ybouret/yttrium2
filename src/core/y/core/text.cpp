#include "y/core/text.hpp"
#include "y/check/usual.hpp"
#include "y/core/utils.hpp"
#include <cstring>
#include <cctype>

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

		char * Text:: Trim(char * const text) noexcept
		{
			const size_t textLength = Length(text);
			char *       curr = text + textLength;
			while (--curr > text)
			{
				char & c = *curr;
				if (isspace(c))
				{
					c = 0;
					continue;
				}
				break;
			}
			return text;
		}


        char * Text:: Add(char * const       outputBuffer,
                          const size_t       outputLength,
                          const char * const text) noexcept
        {
            assert( Good(outputBuffer,outputLength) );
            if(outputLength>0)
            {
                const size_t occupied   = Length(outputBuffer); assert(occupied<outputLength);
                const size_t available  = outputLength-(occupied+1);
                const size_t textLength = Length(text);
                const size_t toCopy     = MinOf(textLength,available);
                char * const target     = outputBuffer+occupied;
                memcpy(target,text,toCopy);
                memset(target+toCopy,0,available-toCopy);
            }
            return outputBuffer;
        }
    }

}
