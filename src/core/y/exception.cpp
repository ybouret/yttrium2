#include "y/exception.hpp"
#include "y/core/text.hpp"
#include "y/core/variadic.hpp"
#include "y/core/utils.hpp"

#include <cstring>
#include <cstdarg>
#include <iostream>
#include <cassert>

namespace Yttrium
{

    void Exception:: clear() noexcept
    {
        memset(tell,0,sizeof(tell));
    }

    Exception:: ~Exception() noexcept
    {
        clear();
    }

    Exception:: Exception() noexcept : std::exception(), tell()
    {
        clear();
    }

    Exception:: Exception(const Exception &other) noexcept :
    std::exception(), tell()
    {
        memcpy(tell,other.tell,sizeof(tell));
    }

    const char * const Exception:: CallSign = "Exception";

    const char * Exception:: what() const noexcept { return CallSign; }
    const char * Exception:: when() const noexcept { return tell; }

    Exception:: Exception(const char * const formatString,...) noexcept :
    tell()
    {
        assert(0!=formatString);
        va_list ap;
        va_start(ap,formatString);
        (void) Core::Variadic::Format(tell,sizeof(tell),formatString,&ap);
        va_end(ap);
    }


    void Exception:: show(std::ostream &os) const
    {
        static const char   header[]   = "*** ";
        static const size_t headerSize = sizeof(header)-1;
        const char * const  prolog     = what();
        const char * const  epilog     = when();
        const size_t        maxLength  = MaxOf( Core::Text::Length(prolog), Core::Text::Length(epilog) );
        const size_t        lineSize   = maxLength+headerSize;;
        Core::Indent(os << '|',  lineSize, '-') << std::endl;
        os << '|' << header << prolog << std::endl;
        os << '|' << header << epilog << std::endl;
        Core::Indent(os << '|', lineSize,'-') << std::endl;
    }


    void Exception:: add(const char * const formatString,...) noexcept
    {
        assert(0!=formatString);
        char buffer[Length];
        {
            va_list ap;
            va_start(ap,formatString);
            (void) Core::Variadic::Format(buffer,sizeof(buffer),formatString,&ap);
            va_end(ap);
        }
        (void) Core::Text::Add(tell, sizeof(tell), buffer);
    }

    void Exception:: pre(const char * const formatString,...) noexcept
    {
        assert(0!=formatString);
        char buffer[Length];
        {
            va_list ap;
            va_start(ap,formatString);
            (void) Core::Variadic::Format(buffer,sizeof(buffer),formatString,&ap);
            va_end(ap);
        }
        (void) Core::Text::Add(buffer, sizeof(buffer), tell);
        memcpy(tell,buffer,Length);
    }


}
