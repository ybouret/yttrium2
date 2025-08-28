
#include "y/apex/number.hpp"
#include "y/system/exception.hpp"
#include <cerrno>

namespace Yttrium
{
    namespace Apex
    {
        Number::  Number() noexcept : Serializable() {}
        Number:: ~Number() noexcept {}

        void Number:: castOverflow(const char * const varName) const
        {
            Libc::Exception excp(EDOM,"overflow for %s cast",callSign());
            if(varName) excp.add(" to %s",varName);
            throw excp;
        }

    }

}
