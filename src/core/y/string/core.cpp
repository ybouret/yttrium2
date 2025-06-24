#include "y/string/core.hpp"
#include "y/check/usual.hpp"
#include "y/type/destroy.hpp"
#include "y/string/stride.hpp"
#include "y/string/length.hpp"
#include "y/sorting/are-equal.hpp"
#include "y/sorting/are-different.hpp"
#include "y/sorting/lexicographic.hpp"
#include "y/type/traits.hpp"
#include "y/stream/output.hpp"
#include "y/stream/input.hpp"
#include "y/system/exception.hpp"
#include "y/decimal.hpp"
#include "y/core/text.hpp"

#include <cstring>

namespace Yttrium
{
    namespace Core
    {

#define Y_String() Container(), Object(), LegacyString(), ContiguousType(), SequenceType(), Serializable()

#undef CH
#define CH char
#include "core.hxx"


#undef CH
#define CH uint32_t
#include "core.hxx"


        template <>
        std::ostream & operator<< <char>(std::ostream & os, const String<char> &self)
        {
            return os << self.c_str();
        }

        template <>
        std::ostream & operator<< <uint32_t>(std::ostream & os, const String<uint32_t> &self)
        {
            const Readable<uint32_t> &_ = self;
            return os << _;
        }

    }

}

