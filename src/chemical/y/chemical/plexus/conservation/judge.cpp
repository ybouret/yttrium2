
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

            std::ostream & operator<<(std::ostream &os, const Broken &broken)
            {
                os << std::setw(22) << broken.xs.str() << " @" << broken.law;
                return os;
            }


            Judge:: ~Judge() noexcept
            {

            }

            Judge:: Judge(const Laws &_laws) :
            laws(_laws),
            zero(),
            bpool(),
            blist(bpool),
            basis(bpool),
            house(laws.clan->size),
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
                blist.free();

                for(const Law *law=laws->head;law;law=law->next)
                {
                    const xreal_t xs = law->excess(xadd,Ctop,TopLevel);
                    if(xs<=zero) continue;
                    const Broken b(*law,xs);
                    blist << b;

                }

                if(blist.size()<=0) return;
                blist.sort(CompareBroken);
                for(const BNode *bn=blist->head;bn;bn=bn->next)
                {
                    Y_XMLog(xml,"[#] " << **bn);
                }

                const size_t nmax = laws.rank;
                house.free();
                basis.free();
                for(size_t i=blist->size;i>0;--i)
                {
                    const Broken & broken = **blist->head;
                    if(Ortho::Vector *v = house.accepts(broken.law.alpha) )
                    {
                        house.progeny(v);
                        basis->pushTail( blist->popHead() );
                        if(house->size>=nmax) break;
                    }
                    else
                    {
                        blist->pushTail(blist->popHead());
                    }
                }

                for(const BNode *bn=basis->head;bn;bn=bn->next)
                {
                    const Broken &broken = **bn;
                    Y_XMLog(xml, "[+] " << broken);
                }

                for(const BNode *bn=blist->head;bn;bn=bn->next)
                {
                    const Broken &broken = **bn;
                    Y_XMLog(xml, "[-] " << broken);
                }



            }

        }

    }

}
