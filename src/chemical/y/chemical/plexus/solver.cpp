
#include "y/chemical/plexus/solver.hpp"
#include "y/stream/libc/output.hpp"
#include "y/format/decimal.hpp"



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
        dC(cluster.slist->size),
        Ceq(cluster->size(),cluster.slist->size),
        affinity(Ceq.rows),
        ppool(),
        plist(ppool),
        psize(),
        basis(ppool),
        xadd(),
        xsum(),
        solve1d(),
        xkin(cluster.slist->size),
        house( new Ortho::House(cluster.slist->size) ),
        lu(cluster.iTopo.rows),
        zero(),
        one(1),
        safety(0.98),
        proExt("pro"),
        gnuplot(),
        exploreName("explore"),
        kineticName("kinetic")
        {

        }


        void Solver:: savePro(const String &baseName, const unsigned  np)
        {
            const String fn = baseName + '.' + proExt;
            OutputFile fp(fn);

            for(unsigned i=0;i<=np;++i) {
                const double u = (i / (double(np)));
                fp("%.15g %s\n", u, (*this)(u).str().c_str());
            }
        }


      

    }

}
