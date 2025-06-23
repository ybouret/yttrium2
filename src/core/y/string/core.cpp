#include "y/string/core.hpp"
#include "y/check/usual.hpp"
#include "y/type/destroy.hpp"
#include "y/string/stride.hpp"
#include "y/string/length.hpp"
#include "y/string/compare.hpp"
#include "y/sorting/are-equal.hpp"
#include "y/type/traits.hpp"

#include <cstring>

namespace Yttrium
{
    namespace Core
    {

#undef CH
#define CH char
#include "core.hxx"


#undef CH
#define CH uint32_t
#include "core.hxx"

    }

}

