
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
            xadd(),
            next(0),
            prev(0)
            {
            }

            void Judge:: trial(XMLog &xml, XWritable &Ctop, Accumulator &Itop)
            {
                Y_XML_Section(xml, "Judge::Trial");
                Y_XMLog(xml, "[[ detect broken ]]");
                {
                    //Y_XML_Section(xml, "Judge::DetectBroken");
                    blist.free();
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
                    }
                }

                {
                    Y_XML_Section(xml, "Judge::Reduction");
                    blist.sort(Broken::Compare);
                    if(xml.verbose)
                    {
                        for(const BNode *bn=blist->head;bn;bn=bn->next)
                        {
                            Y_XMLog(xml, "[+] " << **bn);
                        }
                    }
                }

            }


        }

    }

}
