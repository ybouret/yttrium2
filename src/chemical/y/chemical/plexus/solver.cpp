
#include "y/chemical/plexus/solver.hpp"
#include "y/stream/libc/output.hpp"

#include "y/mkl/opt/minimize.hpp"


namespace Yttrium
{
    namespace Chemical
    {

        using namespace MKL;

        Solver:: ~Solver() noexcept
        {

        }

        Solver:: Solver(const Cluster &cl) :
        cluster(cl),
        Wsub(),
        Csub(cluster.slist->size),
        Cend(cluster.slist->size),
        Ctry(cluster.slist->size),
        Wnew(),
        Cnew(cluster.slist->size),
        Ceq(cluster->size(),cluster.slist->size),
        plist(),
        psize(),
        xadd(),
        xsum(),
        solve1d(),
        xkin(cluster.slist->size),
        zero(),
        one(1)
        {

        }


       
       


    }

}
