
#include "y/chemical/plexus/solver.hpp"
#include "y/stream/libc/output.hpp"
#include "y/vfs/local/fs.hpp"
#include "y/jive/vfs.hpp"

#if 0
#include "y/mkl/numeric.hpp"
#include "y/mkl/api/almost-equal.hpp"
#include "y/mkl/opt/optimize.hpp"
#endif

namespace Yttrium
{
    namespace Chemical
    {

        static inline bool isRunning(const Prospect &pro) noexcept
        {
            assert(Crucial==pro.st||Running==pro.st);
            return Running == pro.st;
        }
        
        bool Solver:: proceed(XMLog &xml, XWritable &Ctop, const XReadable &Ktop)
        {

            Y_XML_Section(xml, "proceed");

            //------------------------------------------------------------------
            //
            //
            // import phase space for the rest of the algorithm
            //
            //
            //------------------------------------------------------------------
            Wsub = zero;
            cluster.dowload(Csub,Ctop);

            if(xml.verbose) {
                Jive::_VFS::OnExtension(LocalFS::Instance(), ".", proExt, Jive::_VFS::Remove);
                gnuplot = "";
            }


            //------------------------------------------------------------------
            //
            //
            // probe all status and process emergency[ies]
            //
            //
            //------------------------------------------------------------------
            unsigned cycles = 0;
            bool     upload = false;
        PROBE:
            {
                ++cycles;
                plist.free();
                bool emergency = false;

                Y_XML_Section_Attr(xml, "probing", Y_XML_Attr(cycles));
                for(const ENode *en = (**cluster).head; en; en=en->next )
                {
                    const Equilibrium &eq = **en;
                    const Status       st = eq.status(Csub, SubLevel);
                    XWritable         &cc = Ceq[plist->size+1].ld(Csub);
                    switch( st )
                    {
                        case Blocked:
                            continue;

                        case Crucial:
                            emergency = true;
                            upload    = true;
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
            //------------------------------------------------------------------
            //
            //
            // Collected all active and valid prospects
            //
            //
            //------------------------------------------------------------------

            // upload if necessary
            if(upload) cluster.upload(Ctop,Csub);


            // finalize
            psize = (xreal_t) (real_t) ( plist->size );
            if(plist->size<=0) {
                Y_XMLog(xml,"[[ all blocked ]]");
                return false;
            }

            assert(plist->size>0);

            // initialize starting point
            Wsub = fullAffinityRMS(Csub,SubLevel);
            

            return true;
        }
        
    }

}


