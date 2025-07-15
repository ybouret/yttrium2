//! \file
#ifndef Y_DFT_Fmt256_Included
#define Y_DFT_Fmt256_Included
#include "y/system/compiler.hpp"
namespace Yttrium {

	//! Format256
	struct DFT_Fmt256 {
		static const unsigned Count=120;     //!< count
		static const uint16_t Table[120][2]; //!< table
		static const size_t   Result=512; //!< 2*size
	};
}
#endif
