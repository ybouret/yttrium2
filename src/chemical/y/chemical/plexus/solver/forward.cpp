
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
            assert(0!=meth);
            const xreal_t Wtmp   = ((*this).*meth)(xml);
            const bool    accept = Wtmp < Wnew;

            Y_XMLog(xml, (accept ?"[+]" : "[-]") << " W_" << uuid << " = " << Wtmp.str()  << " / " << Wnew.str());

            if(accept)
            {
                Wnew = Wtmp;
                Cnew.ld(Ctry);
                Y_XMLog(xml, "check_" << uuid << " : " << affinityRMS(Cnew,SubLevel).str() << " / " << Wnew.str());

                if(Wnew<=zero)
                {
                    Y_XMLog(xml, "numeric zero @" << uuid);
                    cluster.copy(Ctop,TopLevel,Cnew,SubLevel);
                    return Perfect;
                }

                return Success;
            }

            return Stalled;
        }


        void Solver:: forward(XMLog &xml, XWritable &Ctop, const XReadable &Ktop)
        {
            Y_XML_Section(xml,"Solver");

            unsigned cycle = 0;

            if(xml.verbose) OutputFile::Overwrite(monitorFile);

            while(true)
            {
                ++cycle;
                Y_XMLog(xml, "[[ cycle = " << cycle << " ]]");

                // prepare Ctop  and all prospects
                if(!proceed(xml,Ctop,Ktop))
                    return;

                if(1==cycle) OutputFile::Echo(monitorFile,"0 %s 0 #init\n", Wsub.str().c_str());

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
/**/      case Perfect: return;\
/**/      case Success: bestMethod = methodIndx; methodName = & METH##Name; break;\
/**/      case Stalled: break;\
/**/    }\
} while(false)

                Y_Chemical_Solver(explore);
                Y_Chemical_Solver(kinetic);
                Y_Chemical_Solver(jmatrix);

                

                std::cerr << "bestMethod=" << bestMethod << std::endl;

                if(Wnew>=Wsub)
                {
                    assert(bestMethod<0);
                    Y_XMLog(xml, "numeric minimum");
                    return;
                }

                assert(bestMethod>=0);
                assert(0!=methodName);
                cluster.upload(Ctop,Cnew);

                std::cerr << "used " << *methodName << std::endl;
                if(xml.verbose) OutputFile::Echo(monitorFile,"%u %s %d #%s\n",cycle, Wnew.str().c_str(), bestMethod, methodName->c_str());



                if(cycle>=8) break;
            }

        }

    }

}

