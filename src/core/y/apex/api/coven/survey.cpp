#include "y/apex/api/coven/survey.hpp"

namespace Yttrium
{

    namespace Coven
    {
        Survey:: Survey(QVector::Pool &vp) noexcept :
        list(),
        pool(vp),
        calls(0)
        {
        }

        Survey:: ~Survey() noexcept
        {
            reset();
        }
        
        void Survey:: reset() noexcept
        {
            Coerce(calls) = 0;
            while(list.size) pool.store( list.popTail() );
        }


        Survey::ConstInterface & Survey:: locus() const noexcept
        {
            return list;
        }


        void Survey:: collect(XMLog &xml, const QVector &vec)
        {
            ++Coerce(calls);
            for(const QVector * mine=list.head;mine;mine=mine->next)
            {
                if(*mine==vec)
                {
                    return;
                }
            }
            Y_XMLog(xml,"[+] " << vec);
            list.insertOrderedBy( QVector::Compare,  pool.query(vec) );
        }


        bool operator==(const Survey &lhs, const Survey &rhs) noexcept
        {
            if(lhs->size!=rhs->size) return false;

            for(const QVector *l = lhs->head, *r=rhs->head;l;l=l->next,r=r->next)
            {
                assert(l);
                assert(r);
                if( *l != *r ) return false;
            }

            return true;
        }


    }

}


