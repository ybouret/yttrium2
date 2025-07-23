//! \file
#ifndef Y_HASHING_PJW_INCLUDED
#define Y_HASHING_PJW_INCLUDED 1

#include "y/hashing/function.hpp"

namespace Yttrium
{
	namespace Hashing
	{

        //! PJW
		class PJW : public Function
		{
		public:
            //! prototype
			Y_HASHING_FUNCTION_DECL(PJW,4,4);

            //! testing
            static void Tests();
            
		private:
			uint32_t hash;
            Y_Disable_Copy_And_Assign(PJW);
		};
		
	}
}

#endif
