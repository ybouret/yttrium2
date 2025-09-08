
#include "y/chemical/plexus/solver.hpp"
#include "y/container/algorithm/for-each.hpp"
#include "y/stream/libc/output.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        Solver::Result Solver:: upgrade(XMLog &        xml,
                                        XWritable &    Ctop,
                                        const String & uuid,
                                        Proc           meth)
        {
            //__________________________________________________________________
            //
            //
            // apply methods
            //
            //__________________________________________________________________
            assert(0!=meth);
            const xreal_t Wtmp   = ((*this).*meth)(xml);

            //__________________________________________________________________
            //
            //
            // check if numeric zero
            //
            //__________________________________________________________________
            if(Wtmp<=zero)
            {
                Wnew = 0;
                Y_XMLog(xml, "numeric zero @" << uuid);
                cluster.copy(Ctop,TopLevel,Ctry,SubLevel);
                return Perfect;
            }

            //__________________________________________________________________
            //
            //
            // check if accept steps
            //
            //__________________________________________________________________
            const bool    accept = Wtmp < Wnew;
            Y_XMLog(xml, (accept ?"[+]" : "[-]") << " W_" << uuid << " = " << Wtmp.str()  << " / " << Wnew.str());

            if(accept)
            {
                Wnew = Wtmp;
                Cnew.ld(Ctry);
                Y_XMLog(xml, "check_" << uuid << " : " << affinityRMS(Cnew,SubLevel).str() << " / " << Wnew.str());
                return Success;
            }

            return Stalled;
        }


        void Solver:: forward(XMLog &xml, XWritable &Ctop, const XReadable &Ktop)
        {
            Y_XML_Section(xml,"forward");

            unsigned count = 0;

            if(xml.verbose) OutputFile::Overwrite(monitorFile);

            while(true)
            {
                ++count;
                Y_XMLog(xml, "[[ count = " << count << " ]]");

                // prepare Ctop  and all prospects
                if(!proceed(xml,Ctop,Ktop))
                    return;

                if(1==count) OutputFile::Echo(monitorFile,"0 %s 0 #init\n", Wsub.str().c_str());

                Y_XMLog(xml, "W = " << Wsub.str());

                // initialize from starting position
                Wnew = Wsub;
                Cnew.ld(Csub);

                int            bestMethod = -1;
                int            methodIndx = -1;
                const String * methodName = 0;

#define Y_Chemical_Solver(METH) do { \
/**/    switch( ++methodIndx, upgrade(xml, Ctop, METH##Name, & Solver::METH ) ) \
/**/    {\
/**/      case Perfect: goto RETURN;\
/**/      case Success: bestMethod = methodIndx; methodName = & METH##Name; break;\
/**/      case Stalled: break;\
/**/    }\
} while(false)

                Y_Chemical_Solver(explore);
                Y_Chemical_Solver(kinetic);
                Y_Chemical_Solver(jmatrix);


                if(Wnew>=Wsub)
                {
                    assert(bestMethod<0);
                    Y_XMLog(xml, "numeric minimum");
                    goto RETURN;
                }

                assert(bestMethod>=0);
                assert(0!=methodName);
                cluster.upload(Ctop,Cnew);
                if(xml.verbose) OutputFile::Echo(monitorFile,"%u %s %d #%s\n",count, Wnew.str().c_str(), bestMethod, methodName->c_str());

            }

        RETURN:
            if(xml.verbose)
            {
                Y_XML_Section_Attr(xml, "affinity", Y_XML_Attr(count) );
                for(const PNode *pn=plist->head;pn;pn=pn->next)
                {
                    const Prospect & pro = **pn;
                    cluster.nameFmt.display(xml(), pro.eq.name, Justify::Right) << " @" << std::setw(22) << pro.eq.affinity(xadd,pro.eK,Ctop,TopLevel).str() << std::endl;
                }

            }
            return;


        }

    }

}

