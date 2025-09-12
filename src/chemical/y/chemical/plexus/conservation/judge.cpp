
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

            Judge:: Judge(const Act &_act) :
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
                        {
                            {
                                const Broken broken(law,xs);
                                blist << broken;
                            }
                            //Y_XMLog(xml, "[+] " << blist.tail());
                        }
                    }
                    if(blist->size<=0) {
                        Y_XMLog(xml, "[[ no broken law ]]");
                        return;
                    }
                }

                //--------------------------------------------------------------
                //
                //
                // Apply Reduction to smallest correction
                //
                //
                //--------------------------------------------------------------

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
                    broken.law.project(xadd,Ctop,Ctmp);
                    broken.update(Itop);
                    std::cerr << "broken is now " << broken.law.excess(xadd,Ctop,TopLevel).str() << std::endl;
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
                    
                }

            }


        }

    }

}
