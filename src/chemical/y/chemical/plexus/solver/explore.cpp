
#include "y/chemical/plexus/solver.hpp"
#include "y/stream/libc/output.hpp"
#include "y/mkl/numeric.hpp"
#include "y/mkl/api/almost-equal.hpp"
#include "y/mkl/opt/optimize.hpp"
#include "y/jive/vfs.hpp"
#include "y/vfs/local/fs.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        static inline bool isRunning(const Prospect &pro) noexcept
        {
            assert(Crucial==pro.st||Running==pro.st);
            return Running == pro.st;
        }


        void Solver:: explore(XMLog &xml, XWritable &Ctop, const XReadable &Ktop)
        {
            Y_XML_Section(xml, "explore");

            //------------------------------------------------------------------
            //
            //
            // import phase space
            //
            //------------------------------------------------------------------
            cluster.copy(Csub,SubLevel,Ctop,TopLevel);

            //Jive::_VFS::OnExtension(LocalFS::Instance(), ".", "dat", Jive::_VFS::Display);
            Jive::_VFS::OnExtension(LocalFS::Instance(), ".", "dat", Jive::_VFS::Remove);

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


            //------------------------------------------------------------------
            //
            // initialize each direction
            //
            //------------------------------------------------------------------
            Wsub = affinityRMS(Csub,SubLevel);
            Y_XMLog(xml, "Initial RMS = " << Wsub.str());

            Cnew.ld(Csub); // starting point
            Wnew = Wsub;   // starting point

            for(PNode *pn=plist->head;pn;pn=pn->next)
            {
                Prospect          & pro  = **pn;
                pro.W0 = Wsub; // starting point
            }


            //------------------------------------------------------------------
            //
            // optimizing each direction
            //
            //------------------------------------------------------------------
            {
                Y_XML_Section(xml, "optimizing");
                for(PNode *pn=plist->head;pn;pn=pn->next)
                {
                    Prospect &    pro  = **pn; assert(Running == pro.st);
                    optimize(xml,pro);
                }
            }

            //------------------------------------------------------------------
            //
            // sorting and selecting best 1D
            //
            //------------------------------------------------------------------
            {
                const size_t maximum  = cluster->size();
                const size_t selected = plist->size;
                Y_XML_Section_Attr(xml,"selecting", Y_XML_Attr(selected) << Y_XML_Attr(maximum) );
                plist.sort(Prospect::ByIncreasingWo);
                if(xml.verbose)
                {
                    for(PNode *pn=plist->head;pn;pn=pn->next)
                    {
                        Prospect &    pro  = **pn; assert(Running == pro.st);
                        pro.display(xml(),cluster.nameFmt)
                        <<   " $" << std::setw(22) << pro.Wo.str()
                        << " (" << pro.W0.str() <<  " -> " << pro.W1.str() << ")"
                        << std::endl;
                    }
                }

                const Prospect &pro = **plist->head;
                if(pro.Wo<Wnew)
                {
                    Wnew = pro.Wo;
                    Cnew.ld(pro.cc);
                    Y_XMLog(xml, "-- accepted prospect:");
                }
                else
                {
                    Y_XMLog(xml, "-- rejected prospect:");
                }

                if(xml.verbose)
                {
                    pro.display(xml(),cluster.nameFmt) << " $" << std::setw(22) << pro.Wo.str() << " / " << Wsub.str() << std::endl;
                }

            }


        }

    }

}

