
#include "y/object/counted.hpp"


namespace Yttrium
{
    CountedObject::  CountedObject() noexcept : Object(), Counted() {}
    CountedObject:: ~CountedObject() noexcept {}
}
