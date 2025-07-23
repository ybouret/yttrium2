//! \file
#ifndef Y_HASHING_RMD128_INCLUDED
#define Y_HASHING_RMD128_INCLUDED 1


#include "y/hashing/function.hpp"
#include "y/hashing/rmd.hpp"

namespace Yttrium
{
    namespace Hashing
    {
        //! RipeMD-128
        class RMD128 : public Function
		{
		public:
			Y_HASHING_FUNCTION_DECL(RMD128,16,64); //!< specs
			static const size_t RMDsize=128;       //!< 128 bits
            
            
		private:
            Y_Disable_Copy_And_Assign(RMD128);
            RMD      RMD_;
            uint32_t MDbuf[RMDsize/32];
		};
    }
}

#endif
