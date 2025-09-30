
//! \file

#ifndef Y_MKL_FCPU_Included
#define Y_MKL_FCPU_Included 1

#include "y/mkl/xreal.hpp"

namespace Yttrium
{
	namespace MKL
	{
		//! default floating point for CPU
		template <typename T>
		struct FCPU
		{
			typedef T Type; //!< alias

			template <typename U> static inline
				Type Cast(const U& u) { return (Type)u; };
		};

		//! floating point for CPU when using XReal
		template <typename T>
		struct FCPU< XReal<T> >
		{
			typedef T Type; //!< alias

			template <typename U> static inline
				XReal<T> Cast(const U& u) { return (Type)u; };
		};


	}

}

#endif // !Y_MKL_FCPU_Included

