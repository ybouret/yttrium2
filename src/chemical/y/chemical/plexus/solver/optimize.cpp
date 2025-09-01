#include "y/chemical/plexus/solver.hpp"


namespace Yttrium
{
    namespace Chemical
    {
        
        void Solver:: optimize(XMLog &xml, Prospect &pro)
        {

            if(xml.verbose)
                cluster.nameFmt.display(xml(), pro.eq.name, Justify::Right);

            pro.Wo = minimize(xml,pro.W0,pro.W1 = affinityRMS(Cend.ld(pro.cc),SubLevel) );
            pro.xi = pro.eq.extent(xadd,pro.cc.ld(Ctry),SubLevel,Csub);
            
            savePro(pro.eq.name,500);
        }
    }

}


