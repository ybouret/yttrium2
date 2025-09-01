
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
        affinity(cluster->size()),
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
            if(plist->size<=0) return; // done
            psize      = xreal_t( plist->size );

            //Solver & W = *this;

            //------------------------------------------------------------------
            //
            // initialize each direction
            //
            //------------------------------------------------------------------
            const xreal_t  Wsub = affinityRMS(Csub,SubLevel);
            Y_XMLog(xml, "AffinityRMS = " << Wsub.str());

            for(PNode *pn=plist->head;pn;pn=pn->next)
            {
                Prospect          & pro  = **pn;
                const Equilibrium & eq = pro.eq;
                std::cerr << eq.name
                << " ma  = " << eq.massAction(solve1d.xmul,pro.eK,pro.cc,SubLevel).str()
                << " aff = " << eq.affinity(xadd,pro.eK,pro.cc,SubLevel).str()
                << std::endl;

                pro.W0 = Wsub;                   // starting point
                pro.a0 = eq(affinity,SubLevel);  // extract starting own affinity
            }


            //------------------------------------------------------------------
            //
            // optimizing each direction
            //
            //------------------------------------------------------------------
            for(PNode *pn=plist->head;pn;pn=pn->next)
            {
                Prospect &    pro  = **pn; assert(Running == pro.st);
                optimize(xml,pro);
            }

            exit(0);

            // sorting and selecting best 1D
            {
                Y_XML_Section(xml,"selectBest");
                plist.sort(Prospect::ByIncreasingWo);
                Y_XMLog(xml, "// #maximum  = " << cluster->size());
                Y_XMLog(xml, "// #selected = " << plist->size);
                for(PNode *pn=plist->head;pn;pn=pn->next)
                {
                    Prospect &    pro  = **pn; assert(Running == pro.st);
                    //if(xml.verbose)                             pro.display(xml(),cluster.nameFmt) << " $" << std::setw(22) << pro.Wo.str() << " -> " << std::setw(22) << pro.af.str() << " / " << W.affinityRMS(pro.cc,SubLevel).str() << std::endl;
                }
            }





        }



    }

}
