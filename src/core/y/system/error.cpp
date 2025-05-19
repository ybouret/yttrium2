#include "y/system/error.hpp"
#include "y/core/text.hpp"
#include "y/check/usual.hpp"

#include <cstring>
#if defined(_MSC_VER)
#  pragma warning ( disable : 4996 )
#endif

namespace Yttrium
{
	namespace Libc
	{
		char * Error::Format(char * const errorBuffer,
			const size_t errorLength,
			const Type   errorCode) noexcept
		{
			assert(Good(errorBuffer, errorLength));
			return Core::Text::Copy(errorBuffer, errorLength, strerror(errorCode));
		}
	}
}

#if defined(Y_WIN)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
namespace Yttrium
{
	namespace Windows
	{
		char * Error::Format(char * const errorBuffer,
			const size_t errorLength,
			const Type   errorCode) noexcept
		{
			assert(Good(errorBuffer, errorLength));
			::FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, 
				0, 
				errorCode, 
				MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), 
				errorBuffer, 
				DWORD(errorLength), 
				0);
			return Core::Text::Trim(errorBuffer);
		}
	}
}
#endif
