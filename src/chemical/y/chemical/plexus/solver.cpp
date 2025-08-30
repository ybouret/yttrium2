
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
        Csub(cluster.slist->size),
        Cend(cluster.slist->size),
        Ctry(cluster.slist->size),
        Ceq(cluster->size(),cluster.slist->size),
        plist(),
        psize(),
        xadd(),
        xsum(),
        solve1d(),
        zero(),
        one(1)
        {
            
        }


        static inline bool isRunning(const Prospect &pro) noexcept
        {
            assert(Crucial==pro.st||Running==pro.st);
            return Running == pro.st;
        }

        void Solver:: buildProspects(XMLog &xml, XWritable &Ctop, const XReadable &Ktop)
        {
            Y_XML_Section(xml, "buildProspects");

            //------------------------------------------------------------------
            //
            //
            // import phase space
            //
            //------------------------------------------------------------------
            cluster.copy(Csub,SubLevel,Ctop,TopLevel);

            //------------------------------------------------------------------
            //
            //
            // probe all status and process emergency
            //
            //------------------------------------------------------------------
            unsigned cycle = 0;
        PROBE:
            {
                ++cycle;
                Y_XML_Section_Attr(xml, "probing", Y_XML_Attr(cycle));
                plist.free();
                bool emergency = false;
                for(const ENode *en = (**cluster).head; en; en=en->next )
                {
                    const Equilibrium &eq = **en;
                    const Status       st = eq.status(Csub, SubLevel);
                    XWritable         &cc = Ceq[plist->size+1].ld(Csub);
                    switch( st )
                    {
                        case Blocked:  continue;
                        case Crucial:
                            emergency = true;
                            break;

                        case Running:
                            if(emergency) continue;
                            break;
                    }

                    assert(Running == st || Crucial == st);
                    const xreal_t  eK = eq(Ktop,TopLevel);
                    const xreal_t  xi = solve1d( eq, eK, cc, SubLevel, Csub);
                    const Prospect pro(st,eq,eK,cc,xi);
                    if(xml.verbose) pro.display(xml(),cluster.nameFmt) << std::endl;
                    plist << pro;
                    
                }
                if(!emergency) goto BUILD; // all probed, all ok

                //--------------------------------------------------------------
                //
                // process emergency
                //
                //--------------------------------------------------------------
                Y_XMLog(xml, "[[ processing emergency ]]");

                // removing running
                plist.removeIf(isRunning); assert(plist->size>0);

                // sort remaining crucial
                plist.sort(Prospect::ByDecreasingXi);
                const Prospect &crucial = **plist->head; assert(Crucial==crucial.st);

                Y_XMLog(xml, "selected crucial: " << crucial.eq.name);
                // update Csub
                Csub.ld(crucial.cc);
                goto PROBE;
            }

        BUILD:
            if(plist->size<=0) return;
            psize      = xreal_t( plist->size );
            Solver & F = *this;

            {
                const xreal_t  Fsub = affinity(Csub,SubLevel);
                Y_XMLog(xml, "Affinity = " << Fsub.str());

                // optimizing each direction
                for(PNode *pn=plist->head;pn;pn=pn->next)
                {
                    Prospect &    pro  = **pn; assert(Running == pro.st);
                    const xreal_t Fend = pro.a0 = affinity(pro.cc,SubLevel);
                    Cend.ld(pro.cc);

                    {
                        XTriplet xx = { zero, 0, one  };
                        XTriplet ff = { Fsub, 0, Fend };

                        {
                            const String fn = pro.eq.name + ".dat";
                            OutputFile   fp(fn);
                            const unsigned np = 200;
                            for(unsigned i=0;i<=np;++i)
                            {
                                const double u = i / (double(np));
                                fp("%.15g %s\n", u, F(u).str().c_str());
                            }
                        }

                        const xreal_t uopt = Minimize<xreal_t>::Run(Minimizing::Inside,F,xx,ff);
                        std::cerr << "uopt=" << uopt << " @" << pro.eq.name << std::endl;
                        std::cerr << "Ctry=" << Ctry << std::endl;
                        std::cerr << "Csub=" << Csub << std::endl;
                        std::cerr << "Cend=" << Cend << std::endl;

                        pro.xi = pro.eq.extent(xadd, pro.cc.ld(Ctry), SubLevel, Csub);
                        pro.af = ff.b;
                    }

                }

                // sorting and selecting best 1D
                {
                    Y_XML_Section(xml,"selectBest");
                    plist.sort(Prospect::ByIncreasingAF);
                    Y_XMLog(xml, "// #maximum  = " << cluster->size());
                    Y_XMLog(xml, "// #selected = " << plist->size);
                    for(PNode *pn=plist->head;pn;pn=pn->next)
                    {
                        Prospect &    pro  = **pn; assert(Running == pro.st);
                        if(xml.verbose)
                            pro.display(xml(),cluster.nameFmt) << " $" << std::setw(22) << pro.a0.str() << " -> " << std::setw(22) << pro.af.str() << " / " << F.affinity(pro.cc,SubLevel).str() << std::endl;
                    }
                }

            }



        }

    }

}
