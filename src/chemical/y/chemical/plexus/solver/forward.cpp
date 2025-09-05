
#include "y/chemical/plexus/solver.hpp"
#include "y/container/algorithm/for-each.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        bool Solver:: upgrade(XMLog &        xml,
                              XWritable &    Ctop,
                              const String & uuid,
                              Proc           meth)
        {
            assert(0!=meth);
            Y_XML_Section(xml,uuid);

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
                    return true;
                }
            }

            return false;
        }


        void Solver:: forward(XMLog &xml, XWritable &Ctop, const XReadable &Ktop)
        {
            Y_XML_Section(xml,"Solver");

            //unsigned cycle = 1;


            // prepare Ctop  and all prospects
            if(!proceed(xml,Ctop,Ktop))
                return;

            Y_XMLog(xml, "W = " << Wsub.str());

            // initialize from starting position
            Wnew = Wsub;
            Cnew.ld(Csub);

            if( upgrade(xml, Ctop, exploreName, & Solver::explore ) )
            {
                return;
            }

            if( upgrade(xml, Ctop, kineticName, & Solver::kinetic ) )
            {
                return;
            }

            

        }

    }

}

