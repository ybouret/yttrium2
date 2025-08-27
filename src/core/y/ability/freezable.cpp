
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

    void Freezable:: checkpoint(const char * const name) const
    {
        if( frozen() ) throw Specific::Exception(name,"forbidden access (frozen)");
    }

    void Freezable:: checkpoint(const Core::String<char> &s) const
    {
        checkpoint( s.c_str() );
    }


}


