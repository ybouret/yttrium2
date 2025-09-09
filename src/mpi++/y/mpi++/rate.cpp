

#include "y/mpi++/api.hpp"

namespace Yttrium
{
    MPI:: Rate:: Rate() noexcept : bytes(0), ticks(0)
    {
    }

    MPI::Rate:: ~Rate() noexcept
    {

    }

    MPI:: Rate:: Rate(const Rate &_) noexcept : bytes(_.bytes), ticks(_.ticks)
    {
    }

    

}

