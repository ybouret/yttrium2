
#include "y/chemical/plexus/conservation/judge.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        namespace Conservation
        {

            Broken:: ~Broken() noexcept
            {
            }

            Broken:: Broken(const Law & _law, const xreal_t _xs) noexcept :
            law(_law),
            xs(_xs)
            {
            }
            

            Broken:: Broken(const Broken &_) noexcept :
            law(_.law),
            xs(_.xs)
            {
            }

            Judge:: ~Judge() noexcept
            {
                
            }

            Judge:: Judge(const Laws &_laws) :
            laws(_laws),
            zero(),
            jail(),
            xadd()
            {
            }

            static inline
            SignType CompareBroken(const Broken &lhs, const Broken &rhs) noexcept
            {
                return Sign::Of(lhs.xs,rhs.xs);
            }

            void Judge:: abide(XMLog &xml, XWritable &Ctop)
            {
                Y_XML_Section(xml, "abide");
                jail.free();
                for(const Law *law=laws->head;law;law=law->next)
                {
                    const xreal_t xs = law->excess(xadd,Ctop,TopLevel);
                    if(xs<=zero) continue;
                    const Broken b(*law,xs);
                    jail << b;

                }

                if(jail.size()<=0) return;
                jail.sort(CompareBroken);
                for(const BNode *bn=jail->head;bn;bn=bn->next)
                {
                    const Broken &broken = **bn;
                    Y_XMLog(xml, std::setw(22) << broken.xs.str() << " @" << broken.law);
                }

                

            }

        }

    }

}
