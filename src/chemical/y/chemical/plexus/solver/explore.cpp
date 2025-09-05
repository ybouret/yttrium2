
#include "y/chemical/plexus/solver.hpp"
#include "y/stream/libc/output.hpp"
#include "y/mkl/numeric.hpp"
#include "y/mkl/api/almost-equal.hpp"
#include "y/mkl/opt/optimize.hpp"

namespace Yttrium
{
    namespace Chemical
    {


        xreal_t Solver:: explore(XMLog &xml)
        {
            Y_XML_Section(xml,exploreName);

            assert(plist->size>0);

            for(PNode *pn=plist->head;pn;pn=pn->next)
            {
                Prospect & pro  = **pn; assert(Running == pro.st);
                Cend.ld(pro.cc);
                if(xml.verbose) cluster.nameFmt.display(xml(), pro.eq.name, Justify::Right);
                pro.Wo = minimize(xml);
            }
            
            plist.sort(Prospect::ByIncreasingWo);

            if(xml.verbose)
            {
                for(PNode *pn=plist->head;pn;pn=pn->next)
                {
                    Prospect &    pro  = **pn; assert(Running == pro.st);
                    pro.display(xml() << "[+] ",cluster.nameFmt)
                    <<   " $" << std::setw(22) << pro.Wo.str()
                    << std::endl;
                }
            }


            const Prospect &pro = **plist->head;

            if(xml.verbose)
            {
                savePro(pro.eq.name,500);
                pro.display(xml() << "[*] ",cluster.nameFmt) << " $" << std::setw(22) << pro.Wo.str() << " / " << Wsub.str() << std::endl;
                gnuplot = "plot '" + pro.eq.name + '.' + proExt + "' w lp";
                xml() << "\t" << gnuplot << std::endl;
            }

            // provide Ctry to driver
            Ctry.ld(pro.cc);
            return (plist->size > 1) ? pro.Wo : zero;
        }




    }

}

