#include "y/chemical/plexus/solver.hpp"


namespace Yttrium
{
    namespace Chemical
    {

        void Solver:: jmatrix(XMLog &xml)
        {
            Y_XML_Section(xml,jmatrixName);

            house->free();

            size_t n = 0;
            {
                const size_t    nmax = cluster.iTopo.rows;
                Y_XML_Section_Attr(xml, "basis", Y_XML_Attr(nmax) );
                PList::ListType basis;
                try
                {
                    while(plist->size>0)
                    {
                        const Prospect    &pro = **plist->head;
                        const Equilibrium &eq  = pro.eq;
                        const size_t       ei  = eq.indx[SubLevel];
                        if(Ortho::Vector * v = house->accepts( cluster.iFull[ei] ) )
                        {
                            // update status
                            ++n;
                            basis.pushTail( plist->popHead() );
                            house->progeny(v);
                            Y_XMLog(xml, "[+] " << eq);
                            if(n>=nmax)
                                break;
                        }
                        else
                        {
                            Y_XMLog(xml, "[-] " << eq);
                            plist.popHead();
                        }
                    }
                    plist.free();
                    plist->swapListFor(basis);

                }
                catch(...)
                {
                    plist->mergeTail(basis); throw;
                }
            }
            assert(plist->size==n);

        }
    }

}

