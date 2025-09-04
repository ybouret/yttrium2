
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
        exploreName("explore"),
        kineticName("kinetic"),
        jmatrixName("jmatrix"),
        proExt("pro"),
        gnuplot()
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


        void Solver:: run(XMLog & xml, XWritable & Ctop, const XReadable & Ktop)
        {
            Y_XML_Section(xml, "Solver::run" );
            const String xpName = exploreName + ".dat";

            if(xml.verbose) OutputFile::Overwrite(xpName);


            size_t cycle = 1;
            explore(xml,Ctop,Ktop); { AppendFile fp(xpName); fp("0 %s\n", Wsub.str().c_str()); }
            if(Wnew<=zero) goto CONVERGED;
            


        CONVERGED:
            { AppendFile fp(xpName); fp("%s %s\n", Decimal(cycle).c_str(), Wnew.str().c_str()); }

        }




    }

}
