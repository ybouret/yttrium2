
#include "y/chemical/plexus/solver.hpp"
#include "y/container/algorithm/for-each.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        bool Solver:: upgrade(XMLog &xml, const String &uuid, Proc meth)
        {
            assert(0!=meth);
            Y_XML_Section(xml,uuid);

            const xreal_t Wtmp = ((*this).*meth)(xml);

            return false;
        }


        void Solver:: forward(XMLog &xml, XWritable &Ctop, const XReadable &Ktop)
        {
            Y_XML_Section(xml,"Solver");

            // prepare Ctop  and all prospects
            if(!proceed(xml,Ctop,Ktop))
                return;

            Y_XMLog(xml, "W = " << Wsub.str());

            // initialize
            Wnew = Wsub;
            Cnew.ld(Csub);

            upgrade(xml,exploreName, & Solver::explore );
            upgrade(xml,kineticName, & Solver::kinetic );


        }

    }

}

