#include "y/coven/survey.hpp"

namespace Yttrium
{

    namespace Coven
    {
        Survey:: Survey() noexcept :
        list(),
        calls(0)
        {
        }

        Survey:: ~Survey() noexcept
        {
            release();
        }
        
        void Survey:: release() noexcept
        {
            Coerce(calls) = 0;
            list.release();
            // while(list.size) pool.store( list.popTail() );
        }

        void Survey:: reclaim(QVector::Pool &pool) noexcept
        {
            Coerce(calls) = 0;
            while(list.size) pool.store( list.popTail() );
        }


        Survey::ConstInterface & Survey:: locus() const noexcept
        {
            return list;
        }


        void Survey:: collect(XMLog &        xml,
                              const QVector &vec,
                              QVector::Pool &vp)
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
            list.insertOrderedBy( QVector::Compare,  vp.query(vec) );
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


