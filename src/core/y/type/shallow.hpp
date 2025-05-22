

#ifndef Y_Type_Shallow_Included
#define Y_Type_Shallow_Included 1

#include "y/system/compiler.hpp"

namespace Yttrium
{

#define Y_Shallow_Decl(NAME) \
/**/ struct NAME##_ {} ;\
/**/ extern const NAME##_ NAME

#define Y_Shallow_Impl(NAME) const NAME##_ NAME = {}

}

#endif

