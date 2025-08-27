
#include "y/ability/freezable.hpp"
#include "y/system/exception.hpp"
#include "y/string.hpp"

namespace Yttrium
{
    Freezable:: ~Freezable() noexcept {}
    Freezable::  Freezable() noexcept : flag(false) {}

    void Freezable:: freeze() noexcept
    {
        flag = true;
    }

    

    bool Freezable:: frozen() const noexcept
    {
        return flag;
    }

    void Freezable:: checkpoint(const char * const name, const char * const func) const
    {
        assert(func);
        if( frozen() ) throw Specific::Exception(name,"frozen in '%s'",func);
    }

    void Freezable:: checkpoint(const Core::String<char> &s, const char * const func) const
    {
        checkpoint( s.c_str(), func );
    }


}


