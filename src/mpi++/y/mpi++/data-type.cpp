
#include "y/mpi++/api.hpp"

namespace Yttrium
{

    MPI:: DataType:: ~DataType() noexcept
    {

    }

    MPI:: DataType:: DataType(MPI_Datatype          dt,
                              const size_t          sz,
                              const std::type_info &ti) :
    list(),
    size(sz),
    uuid( ti.name() )
    {
        Coerce(list) << dt;
    }

    const String & MPI:: DataType:: key() const noexcept
    {
        return uuid;
    }

    void MPI:: decl(MPI_Datatype          dt,
                    const size_t          sz,
                    const std::type_info &ti)
    {
        DataType::Set   & db  = Coerce(dts);
        DataType::Pointer p   = new DataType(dt,sz,ti);
        const String &    key = p->uuid;

        if( DataType::Pointer * const q = db.search(key) )
        {
            // typeinfo already registered
            DTList & target = Coerce( (**q).list ); assert(target->size>0);
            DTList & source = Coerce( p->list );    assert(1==source->size);
            if( !target.found( **(source->head) ) )
            {
                target->mergeTail(*source);
            }

        }
        else
        {
            // no registered
            if(!db.insert(p))
                throw Specific::Exception(CallSign,"failed to insert '%s'", key.c_str() );
        }

    }

#define Y_MPI_DECL(DT,TYPE) do { decl(MPI_##DT,sizeof(TYPE),typeid(TYPE)); } while(false)

    void MPI:: buildDTS()
    {
        Y_MPI_DECL(FLOAT,float);
        Y_MPI_DECL(DOUBLE,double);

    }


}

