//!\file
#ifndef Y_HASHING_ADLER32_INCLUDED
#define Y_HASHING_ADLER32_INCLUDED 1

#include "y/hashing/function.hpp"

namespace Yttrium
{
	namespace Hashing
	{

        //! Adler32
		class Adler32 : public Function
		{
		public:
            //! prototype
			Y_HASHING_FUNCTION_DECL(Adler32,4,4);
			
		private:
			uint32_t a; //!< internal state
            Y_Disable_Copy_And_Assign(Adler32); //!< discarding
		};
		
	}
}

#endif
