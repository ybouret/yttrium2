
//! \file

#ifndef Y_Coven_Tribe_Included
#define Y_Coven_Tribe_Included 1

#include "y/apex/api/coven/types.hpp"
#include "y/apex/api/coven/ilist.hpp"

#define Y_Coven_Stamp 1

namespace Yttrium
{

    namespace Coven
    {


        class Survey
        {
        public:
            explicit Survey() : list(), trials(0) {}
            virtual ~Survey() noexcept {}

            QVector::List list;
            size_t        trials;

            void collect(const QVector &vec)
            {
                ++trials;
                for(const QVector * mine=list.head;mine;mine=mine->next)
                {
                    if(*mine==vec)
                    {
                        //std::cerr << "[-] " << vec << std::endl;
                        return;
                    }
                }
                std::cerr << "[+] " << vec << std::endl;
                list.insertOrderedBy( QVector::Compare,  new QVector(vec) );
            }


        private:
            Y_Disable_Copy_And_Assign(Survey);
        };

        class Tribe : public Object
        {
        public:
            typedef CxxListOf<Tribe> List;

            template <typename MATRIX>
            explicit Tribe(const MATRIX        &mu,
                           const size_t         first,
                           const IPool         &ip,
                           QFamily::Pool       &fp) :
            Object(),
            basis(ip),
            ready(ip,mu.rows,first),
#if Y_Coven_Stamp
            stamp(ip),
#endif
            fpool(fp),
            family( fpool.start(mu[first]) ),
            next(0),
            prev(0)
            {
                assert(ready->size==mu.rows);
                if(family) {
                    try {
                        basis->pushTail( ready->popHead() );
#if Y_Coven_Stamp
                        stamp << first;
#endif
                    }
                    catch(...) { quit(); throw; }
                }
                else
                {
                    ready.free();
                }
            }

            virtual ~Tribe() noexcept;

            friend std::ostream & operator<<(std::ostream &, const Tribe &);

            void remove(const size_t indx) noexcept;

            template <typename MATRIX> inline
            void generate(Tribe::List & heirs, const MATRIX &mu, Survey * const survey)
            {
                assert(family);
                Tribe::List H;
                for(const INode *node = ready->head; node; node=node->next)
                {
                    //----------------------------------------------------------
                    // try to expand family
                    //----------------------------------------------------------
                    const size_t    indx    = **node;
                    QFamily * const lineage = family->newFamilyWith(mu[indx],fpool);
                    if(!lineage) continue;

                    //----------------------------------------------------------
                    // a new vector was created into lineage
                    //----------------------------------------------------------
                    assert(0!=lineage->lastVec);
                    try {
                        Coerce( H.pushTail( new Tribe(*this,indx) )->family ) = lineage;
                    }
                    catch(...)
                    {
                        fpool.store(lineage); throw;
                    }

                    if(survey) survey->collect(*(lineage->lastVec));
                }
                H.sort(Tribe::Compare);
                Tribe::List all;
                all.fusion(heirs,H,Tribe::Compare);
                heirs.swapListFor(all);
            }

            static SignType Compare(const Tribe * const, const Tribe * const) noexcept;
            


            // members
            IList           basis; //!< ordered indices
            IList           ready; //!< availavle indices
#if Y_Coven_Stamp
            IList           stamp; //!< stamp
#endif
            QFamily::Pool & fpool;   //!< persisent family pool
            QFamily * const family;  //!< current family or NULL
            Tribe *         next;    //!< for list
            Tribe *         prev;    //!< for list

        private:
            Y_Disable_Copy_And_Assign(Tribe);
            void quit() noexcept; //!< make no family
            explicit Tribe(const Tribe &sire, const size_t indx) :
            Object(),
            basis(sire.basis),
            ready(sire.ready),
#if Y_Coven_Stamp
            stamp(sire.stamp),
#endif
            fpool(sire.fpool),
            family(0),
            next(0),
            prev(0)
            {
                basis.sorted(indx);
                ready.remove(indx);
#if Y_Coven_Stamp
                stamp << indx;
#endif
            }

        };


 

    }

}

#endif

