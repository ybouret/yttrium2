
#include "y/mpi++/api.hpp"
#include "y/utest/run.hpp"

#include "y/container/associative/hash/map.hpp"
#include "y/hashing/des64.hpp"

using namespace Yttrium;

namespace Yttrium
{
    class MPI_DT_Hasher
    {
    public:
        MPI_DT_Hasher() {}
        ~MPI_DT_Hasher() {}

        size_t operator()(const MPI_Datatype &dt) const noexcept
        {
            union
            {
                uint64_t     qw;
                uint32_t     dw[2];
                MPI_Datatype dt;
                size_t       sz;
            } alias = { 0 };
            alias.dt = dt;
            mix(alias.dw[0],alias.dw[1]);
            return alias.sz;
        }

        Hashing::DES64 mix;

    private:
        Y_Disable_Copy_And_Assign(MPI_DT_Hasher);
    };

    class DatatypeInfo : public CountedObject
    {
    public:
        explicit DatatypeInfo(const MPI_Datatype &dt, const size_t dtlen);

    private:
        Y_Disable_Copy_And_Assign(DatatypeInfo);
    };


}

Y_UTEST(excp)
{
    {
        const MPI::Exception excp(MPI_ERR_OTHER,"bad at %d", __LINE__);
        excp.show(std::cerr);
    }

    HashMap<MPI_Datatype,size_t,MPI_DT_Hasher> dtmap;

    Y_PRINTV( dtmap.hash(MPI_CHAR)   );
    Y_PRINTV( dtmap.hash(MPI_INT)    );
    Y_PRINTV( dtmap.hash(MPI_DOUBLE) );
    Y_PRINTV( dtmap.hash(MPI_FLOAT)  );






}
Y_UDONE()

