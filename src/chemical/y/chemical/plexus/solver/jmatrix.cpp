
#include "y/chemical/plexus/solver.hpp"
#include "y/container/algorithm/for-each.hpp"


namespace Yttrium
{
    namespace Chemical
    {

        xreal_t Solver:: jmatrix(XMLog &xml)
        {
            Y_XML_Section(xml,jmatrixName);

            assert(plist->size>0);

            //__________________________________________________________________
            //
            //
            //
            // extract basis
            //
            //
            //__________________________________________________________________
            house->free();
            basis.free();
            {
                const size_t    nmax = cluster.iTopo.rows;
                Y_XML_Section_Attr(xml, "basis", Y_XML_Attr(nmax) );

                for(const PNode *pn=plist->head;pn;pn=pn->next)
                {
                    const Prospect    &pro = **pn;
                    const Equilibrium &eq  = pro.eq;
                    const size_t       ei  = eq.indx[SubLevel];
                    if(Ortho::Vector * v = house->accepts( cluster.iFull[ei] ) )
                    {
                        house->progeny(v);
                        Y_XMLog(xml, "[+] " << eq);
                        if( (basis << pro)->size >= nmax ) break;
                    }
                    else
                    {
                        Y_XMLog(xml, "[-] " << eq);
                    }
                }
            }

            assert(basis->size>0);
            house->free();

            //__________________________________________________________________
            //
            //
            //
            // build jacobian matrix @Csub
            //
            //
            //__________________________________________________________________
            const size_t n = basis->size;
            const size_t m = cluster.slist->size;
            NRContext   &_ = nrctx[n];
            XMatrix & dA = _.dA;
            XMatrix & Nu = _.Nu;
            XArray  & Xi = _.Xi;
            XMatrix &  J = _.J;

            dA.ld(zero);
            {
                size_t i = 1;
                for(const PNode *pn=basis->head;pn;pn=pn->next,++i)
                {
                    const Prospect    &pro = **pn;
                    const Equilibrium &eq = pro.eq;
                    const size_t       ei = eq.indx[SubLevel];

                    eq.jacobian(dA[i],Csub,SubLevel);
                    Nu[i].ld( cluster.xFull[ei] );
                    Xi[i] = -eq.affinity(xadd,pro.eK,Csub,SubLevel);
                }
            }

            for(size_t i=n;i>0;--i)
            {
                XMatrix::Row       & Ji = J[i];
                const XMatrix::Row &dAi = dA[i];
                for(size_t j=n;j>0;--j)
                {
                    xadd.ldz();
                    xadd.addProd(dAi(),Nu[j](),m);
                    Ji[j] = xadd.sum();
                }
            }

            

            //__________________________________________________________________
            //
            //
            //
            // compute Xi
            //
            //
            //__________________________________________________________________
            if(!lu.build(J))
            {
                Y_XMLog(xml,"Singular Jacobian");
                //std::cerr << "C=" << Csub << std::endl;
                //std::cerr << "dA=" << dA << std::endl;
                //std::cerr << "Nu=" << Nu << std::endl;
                //std::cerr << "J=" << J << std::endl;
                //exit(0);
                return Wsub;
            }

            lu.solve(J,Xi);

            //__________________________________________________________________
            //
            //
            //
            // compute dC
            //
            //
            //__________________________________________________________________
            xreal_t scale  = 1.1;
            bool    wasCut = false;
            for(const SNode *sn=cluster.slist->head;sn;sn=sn->next)
            {
                const size_t j = (**sn).indx[SubLevel];
                xadd.ldz();
                for(size_t i=n;i>0;--i)
                    xadd.addProd(Xi[i],Nu[i][j]);
                const xreal_t dc = (dC[j] = xadd.sum() );
                if(dc<zero)
                {
                    wasCut = true;
                    InSituMin(scale, Csub[j]/(-dc));
                }

            }
            if(wasCut) scale *= safety;
            Y_XMLog(xml, "[" << (wasCut ? "need rescaling" : "no rescaling") << "] scale=" << scale.str());

            for(size_t j=dC.size();j>0;--j)
                Cend[j] = Csub[j] + scale * dC[j];

            savePro(jmatrixName,500);

            if(xml.verbose) xml() << jmatrixName;
            const xreal_t Wjmx = minimize(xml);
            Y_XMLog(xml, "Wjmx=" << Wjmx.str() << " / " << Wnew.str() );

            if(xml.verbose)
            {
                gnuplot += ", '" + jmatrixName + '.' + proExt + "' w lp";
                xml() << "\t" << gnuplot << std::endl;
            }

            return Wjmx;
        }


    }

}


