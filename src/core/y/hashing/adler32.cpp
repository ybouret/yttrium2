#include "y/hashing/adler32.hpp"

namespace Yttrium
{
	namespace Hashing
	{
		
		Adler32:: Adler32() noexcept : Function( __length, __window ), a(0)
		{
		}
		
        Adler32:: ~Adler32() noexcept
		{
			a = 0;
		}
        
        const char * const  Adler32:: CallSign = "Adler32";
        
		void Adler32:: set() noexcept
		{
			a = 1;
		}
		
#define BASE 65521
		void Adler32:: run( const void *buffer, size_t buflen ) noexcept
		{
			assert( !(buffer==NULL&&buflen>0) );
			const uint8_t *buf = (const uint8_t *)buffer;
			uint32_t       s1  =  a & 0xffff;
			uint32_t       s2  = (a >> 16) & 0xffff;
			size_t         n   = 0;
			for(; n < buflen; ++n) 
			{
				s1 = (s1 + buf[n]) % BASE;
				s2 = (s2 + s1)     % BASE;
			}
			a  = (s2 << 16) + s1;
		}
		
		void Adler32:: get( void *output, size_t outlen ) noexcept
		{
			fill(output, outlen, &a, sizeof(a) );
		}
		
		
	}
	
}

