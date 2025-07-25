//! \file
#ifndef Y_HASHING_RMD160_INCLUDED
#define Y_HASHING_RMD160_INCLUDED 1


#include "y/hashing/function.hpp"
#include "y/hashing/rmd.hpp"

namespace Yttrium
{
    namespace Hashing
    {
        //! RipeMD 160
        class RMD160 : public Function
		{
		public:
			Y_HASHING_FUNCTION_DECL(RMD160,20,64); //!< specs
			static const size_t RMDsize=160;       //!< bits
            
            static void Tests(); //!< testing
            
		private:
            Y_Disable_Copy_And_Assign(RMD160); //!< discarding
            RMD      RMD_;                     //!< inner rmd
            uint32_t MDbuf[RMDsize/32];        //!< inner state
		};
    }
}

#endif
