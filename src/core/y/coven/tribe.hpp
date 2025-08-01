
//! \file

#ifndef Y_Coven_Tribe_Included
#define Y_Coven_Tribe_Included 1

#include "y/coven/survey.hpp"
#include "y/coven/ilist.hpp"


namespace Yttrium
{

    namespace Coven
    {

        //______________________________________________________________________
        //
        //
        //
        //! Tribe = basis + ready + family
        //
        //
        //______________________________________________________________________
        class Tribe : public Object
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            typedef CxxListOf<Tribe> List; //!< alias


            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup
            /**
             \param mu a compatible matrix
             \param first index of first row to process
             \param ip    shared IPool
             \param fp    persistent family pool, fp.dimensions == mu.cols
             */
            template <typename MATRIX>
            explicit Tribe(const MATRIX        &mu,
                           const size_t         first,
                           const IPool         &ip,
                           QFamily::Pool       &fp) :
            Object(),
            basis(ip),
            ready(ip,mu.rows,first),
            fpool(fp),
            family( fpool.start(mu[first]) ),
            next(0),
            prev(0)
            {
                assert(ready->size==mu.rows);
                if(family) {
                    try {
                        basis->pushTail( ready->popHead() );
                    }
                    catch(...) { quit(); throw; }
                }
                else
                {
                    ready.free();
                }
                assert( IList::AreDetached(ready,basis) );
            }

            //! cleanup
            virtual ~Tribe() noexcept;

            //! display
            friend std::ostream & operator<<(std::ostream &, const Tribe &);

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! remove index from all indices \param indx bad index (zero/colinear vector)
            void remove(const size_t indx) noexcept;


            //! \return compared by basis + ready
            static SignType Compare(const Tribe * const, const Tribe * const) noexcept;

            //! \return true is same basis and ready
            static bool     AreIdentical(const Tribe * const, const Tribe * const) noexcept;


            //! \return true if no more possible vector
            bool stalled() const noexcept;


            //! create next generation
            /**
             \param xml           output
             \param heirs         list of heirs, pre-sorted
             \param mu            original matrix to process
             \param survey        optional survey to take on newly created vectors
             \param useHyperPlane optimizing last search
             \return number of new tribe(s)
             */
            template <typename MATRIX> inline
            size_t generate(XMLog &        xml,
                            Tribe::List  & heirs,
                            const MATRIX & mu,
                            Survey * const survey,
                            const    bool  useHyperPlane)
            {
                assert(family);
                switch(family->quality)
                {
                    case Ortho::Generating: return generating(xml,heirs,mu,survey);
                    case Ortho::HyperPlane: return useHyperPlane ? hyperplane(xml,mu,survey) : generating(xml,heirs,mu,survey);
                    case Ortho::Basis: break;
                }
                return 0;
            }




            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            IList           basis; //!< ordered   indices
            IList           ready; //!< available indices
            QFamily::Pool & fpool;   //!< persisent family pool
            QFamily * const family;  //!< current family or NULL
            Tribe *         next;    //!< for list
            Tribe *         prev;    //!< for list

        private:
            Y_Disable_Copy_And_Assign(Tribe); //!< discarding
            void quit() noexcept; //!< make no family

            //! partial setup, assign family after construction
            /**
             \param sire parent tribe to copy
             \param indx index to remove from ready and add to basis
             */
            explicit Tribe(const Tribe &sire, const size_t indx) :
            Object(),
            basis(sire.basis),
            ready(sire.ready),
            fpool(sire.fpool),
            family(0),
            next(0),
            prev(0)
            {
                basis.sorted(indx);
                ready.remove(indx);
            }

            //! default generating function
            /**
             \param xml    output
             \param heirs  pre-sorted heirs
             \param mu     original matrix
             \param survey optional survey
             \return number of generated tribe(s)
             */
            template <typename MATRIX> inline
            size_t generating(XMLog &        xml,
                              Tribe::List  & heirs,
                              const MATRIX & mu,
                              Survey * const survey)
            {
                Y_XMLog(xml,"[@] " << basis << ":" << ready);
                assert( IList::AreDetached(basis,ready) );
                Tribe::List offspring;
                {
                    //----------------------------------------------------------
                    // try to create new family and keep track of colinear rows
                    //----------------------------------------------------------
                    IList colinear(basis.pool);
                    for(const INode *node = ready->head; node; node=node->next)
                    {
                        //------------------------------------------------------
                        // try to expand family
                        //------------------------------------------------------
                        const size_t    indx    = **node; assert(!basis.found(indx));
                        QFamily * const lineage = family->newFamilyWith(mu[indx],fpool);
                        if(!lineage)
                        {
                            // row is in vector space
                            colinear << indx;
                           // Y_XMLog(xml,"[-] colinear row#" << indx << " = " << mu[indx]);
                            continue;
                        }

                        //------------------------------------------------------
                        // a new vector was created into lineage
                        //------------------------------------------------------
                        assert(0!=lineage->lastVec);
                        try {
                            Coerce( offspring.pushTail( new Tribe(*this,indx) )->family ) = lineage;
                        }
                        catch(...)
                        {
                            fpool.store(lineage); throw;
                        }
                        
                        //------------------------------------------------------
                        // process the new vector
                        //------------------------------------------------------
                        if(survey) survey->collect(xml,*(lineage->lastVec),fpool.vpool);
                        //std::cerr << "new tribe: " << offspring.tail->basis << ":" << offspring.tail->ready << std::endl;
                    }

                    if(colinear->size>0)
                    {
                        //std::cerr << "processing colinear=" << colinear << std::endl;
                        Tribe::List list;
                        while(offspring.size>0)
                        {
                            Tribe * const tr = offspring.head;
                            for(const INode *node=colinear->head;node;node=node->next)
                            {
                                const size_t indx = **node;
                                assert(!tr->basis.found(indx));
                                tr->ready.remove(indx);
                                tr->basis.sorted(indx);
                            }
                            //std::cerr << "-> " << tr->basis << ":" << tr->ready << std::endl;
                            assert( IList::AreDetached(tr->basis,tr->ready));
                            if(tr->ready->size<=0)
                            {
                                delete offspring.popHead();
                            }
                            else
                            {
                                list.pushTail( offspring.popHead() );
                            }
                        }
                        offspring.swapListFor(list);
                    }
                }

                const size_t res = offspring.size;
                Tribe::List all;
                offspring.sort(Tribe::Compare);
                all.fusion(heirs,offspring,Tribe::Compare);
                heirs.swapListFor(all);
                return res;
            }

            //! hyperplane, would generate at most one new vector
            /**
             \param xml    output
             \param mu     original matrix
             \param survey optional survey
             \return 0, no more tribes
             */
            template <typename MATRIX> inline
            size_t hyperplane(XMLog        & xml,
                              const MATRIX & mu,
                              Survey * const survey)
            {
                assert(family);
                for(const INode *node = ready->head; node; node=node->next)
                {
                    const size_t    indx = **node;
                    QVector * const qvec = family->accepts(mu[indx]);
                    if(!qvec) continue;
                    try
                    {
                        if(survey) survey->collect(xml,*qvec,fpool.vpool);
                        fpool.vpool.store(qvec);
                        return 0;
                    }
                    catch(...)
                    {
                        fpool.vpool.store(qvec); throw;
                    }
                }
                return 0;
            }

        };




    }

}

#endif

