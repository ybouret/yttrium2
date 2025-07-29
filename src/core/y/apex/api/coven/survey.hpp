//! \file
//!
#ifndef Y_Coven_Survey_Included
#define Y_Coven_Survey_Included 1

#include "y/apex/api/coven/types.hpp"


namespace Yttrium
{

    namespace Coven
    {


        class Survey : public Ingress< const Core::ListOf<QVector> >
        {
        public:
            explicit Survey(QVector::Pool &vp) noexcept;
            virtual ~Survey() noexcept;

            void reset() noexcept;

            void collect(const QVector &vec)
            {
                ++Coerce(calls);
                for(const QVector * mine=list.head;mine;mine=mine->next)
                {
                    if(*mine==vec)
                    {
                        //std::cerr << "[-] " << vec << std::endl;
                        return;
                    }
                }
                std::cerr << "[+] " << vec << std::endl;
                list.insertOrderedBy( QVector::Compare,  pool.query(vec) );
            }


        private:
            Y_Disable_Copy_And_Assign(Survey);
            virtual ConstInterface & locus() const noexcept;

            QVector::List   list;
            QVector::Pool & pool;
        public:
            const size_t    calls;
        };
    }

}

#endif

