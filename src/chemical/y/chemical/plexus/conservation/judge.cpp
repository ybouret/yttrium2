
#include "y/chemical/plexus/conservation/judge.hpp"


namespace Yttrium
{
    namespace Chemical
    {
        namespace Conservation
        {
            Judge:: ~Judge() noexcept
            {
            }

            Judge:: Judge(const Cluster & _cl, const Act &_act) :
            cluster(_cl),
            act(_act),
            blist(),
            slist(),
            xadd(),
            Ctmp( act.getMaxActors() ),
            zero(0),
            next(0),
            prev(0)
            {
            }

            void Judge:: trial(XMLog &       xml,
                               XWritable &   Ctop,
                               Accumulator & Itop)
            {
                Y_XML_Section(xml, "Judge::Trial");
                if( const Law *law = lastCase(xml,Ctop,Itop) )
                {
                    Y_XMLog(xml, "need to clear " << *law);
                    Y_XMLog(xml, "with " << act.elist);
                }
            }

            const Law * Judge:: lastCase(XMLog &       xml,
                                      XWritable &   Ctop,
                                      Accumulator & Itop)
            {
                Y_XML_Section(xml, "Judge::LastCase");

                blist.free();
                slist.free();
                //--------------------------------------------------------------
                //
                //
                // detect all broken law(s)
                //
                //
                //--------------------------------------------------------------
                {
                    for(const LNode *ln = (**act).head;ln;ln=ln->next)
                    {
                        const Law &   law = **ln;
                        const xreal_t xs = law.excess(xadd,Ctop,TopLevel);
                        if(xs>zero)
                            blist << Broken(law,xs);
                    }
                    if(blist->size<=0) {
                        Y_XMLog(xml, "[[ no broken law ]]");
                        return 0;
                    }
                }

                //--------------------------------------------------------------
                //
                //
                // Apply Reduction to smallest correction
                //
                //
                //--------------------------------------------------------------
                const Law * clear = 0;
            FIX:
                blist.sort(Broken::Compare);
                if(xml.verbose)
                {
                    bool show = true;
                    for(const BNode *bn=blist->head;bn;bn=bn->next)
                    {
                        Y_XMLog(xml, "[+] " << **bn << (show ? " <-- " : ""));
                        show = false;
                    }
                }

                {
                    const Broken &broken = **blist->head;
                    clear = & broken.law;
                    clear->project(xadd,Ctop,Ctmp);
                    broken.upgrade(Itop);
                    if(xml.verbose)
                    {
                        (**blist->head).still(xadd,Ctop);
                        xml() <<  "[*] " << broken << " <==" << std::endl;
                    }
                }


                //--------------------------------------------------------------
                //
                //
                // update
                //
                //
                //--------------------------------------------------------------
                blist.popHead();
                for(size_t i=blist->size;i>0;--i)
                {
                    Broken &broken = **blist->head;
                    if(broken.still(xadd,Ctop))
                    {
                        blist->moveHeadToTail();
                    }
                    else
                    {
                        Y_XMLog(xml, "[-] " << broken);
                        blist.popHead();
                    }
                }

                if(blist->size<=0)
                {
                    Y_XMLog(xml, "[[ fixed ]] clear=" << *clear);
                    return clear;
                }
                goto FIX;
            }


        }

    }

}
