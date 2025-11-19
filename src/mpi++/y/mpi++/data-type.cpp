
#include "y/mpi++/api.hpp"

namespace Yttrium
{

    MPI:: DataType:: ~DataType() noexcept
    {

    }

    MPI:: DataType:: DataType(MPI_Datatype          dt,
                              const size_t          sz,
                              const std::type_info &ti) :
    info(dt),
    size(sz),
    uuid( ti.name() )
    {
        
    }

    const String & MPI:: DataType:: key() const noexcept
    {
        return uuid;
    }

    void MPI:: decl(MPI_Datatype          dt,
                    const size_t          sz,
                    const std::type_info &ti)
    {
        const DataType::Pointer dtp = new DataType(dt,sz,ti);
        (void) Coerce(dts).insert(dtp);
          //  throw Specific::Exception(CallSign,"Multiple '%s'", dtp->key().c_str());
    }

}

