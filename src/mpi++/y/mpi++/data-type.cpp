
#include "y/mpi++/api.hpp"
#include "y/calculus/integer-log2.hpp"

namespace Yttrium
{

    MPI:: DataType:: ~DataType() noexcept
    {

    }

    MPI:: DataType:: DataType(MPI_Datatype          dt,
                              const unsigned        sh,
                              const std::type_info &ti) :
    list(),
    ishl( sh ),
    uuid( ti.name() )
    {
        Coerce(list) << dt;
    }

    const String & MPI:: DataType:: key() const noexcept
    {
        return uuid;
    }

    uint64_t MPI:: DataType:: bytesFor(const size_t count) const
    {
        // TODO: check max

        return (count << ishl);
    }


    MPI_Datatype  MPI:: DataType:: type() const noexcept
    {
        assert(list->size>0);
        return **(list->head);
    }

    void MPI:: decl(MPI_Datatype          dt,
                    const unsigned        sh,
                    const std::type_info &ti)
    {
        DataType::Set   & db  = Coerce(dts);
        DataType::Pointer p   = new DataType(dt,sh,ti);
        const String &    key = p->uuid;

        if( DataType::Pointer * const q = db.search(key) )
        {
            // typeinfo already registered, update list if necessary
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

#define Y_MPI_DECL(DT,TYPE) do { decl(MPI_##DT,IntegerLog2For<TYPE>::Value,typeid(TYPE)); } while(false)

    void MPI:: buildDTS()
    {
        Y_MPI_DECL(FLOAT,float);
        Y_MPI_DECL(DOUBLE,double);
        Y_MPI_DECL(INT,int);
        Y_MPI_DECL(UNSIGNED,unsigned);
    }

    const MPI:: DataType & MPI:: getDataType( const std::type_info &ti ) const
    {
        const String                     key = ti.name();
        const DataType::Pointer * const  pDT = dts.search(key);
        if(!pDT) throw Specific::Exception(CallSign,"no DataType for '%s'", key.c_str());
        return **pDT;
    }



}

