
#include "y/chemical/plexus/solver.hpp"
#include "y/stream/libc/output.hpp"

#include "y/mkl/opt/optimize.hpp"


namespace Yttrium
{
    namespace Chemical
    {

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
                plist.sort(Prospect::ByDecreasingAX);
                const Prospect &crucial = **plist->head; assert(Crucial==crucial.st);

                // update Csub
                Csub.ld(crucial.cc);
                goto PROBE;
            }

        BUILD:
            if(plist->size<=0) return;
            psize = xreal_t( plist->size );

            // optimizing each direction
            {
                Solver &F = *this;
                const xreal_t Fsub = affinity(Csub,SubLevel);
                Y_XMLog(xml, "Fsub = " << Fsub.str());
                for(PNode *pn=plist->head;pn;pn=pn->next)
                {
                    Prospect & pro = **pn;
                    assert(Running == pro.st);
                    xreal_t Fend   = affinity(pro.cc,SubLevel);
                    Cend.ld(pro.cc);
                    pro.display(std::cerr,cluster.nameFmt) << " $" << Fend.str() << " / " << F(zero).str() << " -> " << F(one).str() << std::endl;

                    XTriplet xx = { zero, 0, one  };
                    XTriplet ff = { Fsub, 0, Fend };

                    {
                        const String fn = pro.eq.name + ".dat";
                        OutputFile   fp(fn);
                        const unsigned np = 100;
                        for(unsigned i=0;i<=np;++i)
                        {
                            const double u = i / (double(np));
                            fp("%.15g %s\n", u, F(u).str().c_str());
                        }
                    }



                }
            }



        }

    }

}
