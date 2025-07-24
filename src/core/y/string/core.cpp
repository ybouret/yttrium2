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
#include "y/format/decimal.hpp"
#include "y/core/text.hpp"
#include "y/container/algorithm/reverse.hpp"

#include <cstring>

namespace Yttrium
{
    namespace Core
    {

#define Y_String() Container(), Object(), LegacyString(), ContiguousType(), SequenceType(), Serializable(), Memory::ReadOnlyBuffer()

#undef CH
#define CH char
#include "core.hxx"


#undef CH
#define CH uint32_t
#include "core.hxx"


        template <>
        std::ostream & String<char>::print(std::ostream & os) const
        {
            return os <<  c_str();
        }

        template <>
        std::ostream & String<uint32_t>::print(std::ostream & os) const
        {
            const Readable<uint32_t> &_ = *this;
            return os << _;
        }

    }

}

