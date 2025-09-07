
#include "y/chemical/plexus/solver.hpp"
#include "y/stream/libc/output.hpp"
#include "y/format/decimal.hpp"



namespace Yttrium
{
    namespace Chemical
    {

        using namespace MKL;

        Solver:: NRContext:: ~NRContext() noexcept
        {
        }

        Solver:: NRContext:: NRContext(const size_t n, const size_t m) :
        dA(n,m),
        Nu(n,m),
        J(n,n),
        Xi(n)
        {
        }


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
        nrctx(cluster.iTopo.rows),
        lu(cluster.iTopo.rows),
        zero(),
        one(1),
        safety(0.98),
        proExt("pro"),
        gnuplot(),
        exploreName("explore"),
        kineticName("kinetic"),
        jmatrixName("jmatrix"),
        monitorFile("monitor.dat")
        {

            for(size_t n=1;n<=cluster.iTopo.rows;++n)
                nrctx.push(n,cluster.slist->size);
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
