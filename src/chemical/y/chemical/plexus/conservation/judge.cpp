
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
            xadd()
            {
            }

            void Judge:: trial(XMLog &xml, XWritable &Ctop)
            {
                Y_XML_Section(xml, "Judge::Trial");

                {
                    Y_XML_Section(xml, "Judge::DetectBroken");
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
                            Y_XMLog(xml, "[+] " << blist.tail());
                        }

                    }
                }

            }


        }

    }

}
