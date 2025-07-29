
//! \file

#ifndef Y_Coven_Tribe_Included
#define Y_Coven_Tribe_Included 1

#include "y/apex/api/coven/survey.hpp"
#include "y/apex/api/coven/ilist.hpp"


//! set to 1 to check that all basis are different
#define Y_Coven_Stamp 1

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

            //! create next generation
            /**
             \param heirs list of heirs, pre-sorted
             \param mu    original matrix to process
             \param survey optional survey to take on newly created vectors
             */
            template <typename MATRIX> inline
            void generate(Tribe::List  & heirs,
                          const MATRIX & mu,
                          Survey * const survey,
                          const    bool  useHyperPlane)
            {
                assert(family);
                switch(family->quality)
                {
                    case Apex::Ortho::Generating: return generating(heirs,mu,survey);
                    case Apex::Ortho::Basis:      return;
                    case Apex::Ortho::HyperPlane: return useHyperPlane ? hyperplane(mu,survey) : generating(heirs,mu,survey);
                }

            }




            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________

            IList           basis; //!< ordered   indices
            IList           ready; //!< available indices
#if Y_Coven_Stamp
            IList           stamp; //!< stamp
#endif
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

            //! default generating function
            /**
             \param heirs  pre-sorted heirs
             \param mu     original matrix
             \param survey optional survey
             */
            template <typename MATRIX> inline
            void generating(Tribe::List  & heirs,
                             const MATRIX & mu,
                             Survey * const survey)
            {
                Tribe::List H; // local heirs
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

                    //----------------------------------------------------------
                    // process the new vector
                    //----------------------------------------------------------
                    if(survey) survey->collect(*(lineage->lastVec));

                }
                H.sort(Tribe::Compare);
                Tribe::List all;
                all.fusion(heirs,H,Tribe::Compare);
                heirs.swapListFor(all);
            }

            //! hyperplane, would generate at most one new vector
            /**
             \param mu     original matrix
             \param survey optional survey
             */
            template <typename MATRIX> inline
            void hyperplane(const MATRIX & mu,
                            Survey * const survey)
            {
                assert(family);
                for(const INode *node = ready->head; node; node=node->next)
                {
                    const size_t    indx = **node;
                    QVector * const qvec = family->accepts(mu[indx]);
                    if(!qvec) continue;
                    //std::cerr << "hyperplane: found " << *qvec << std::endl;
                    try
                    {
                        if(survey) survey->collect(*qvec);
                        fpool.vpool.store(qvec);
                    }
                    catch(...)
                    {
                        fpool.vpool.store(qvec); throw;
                    }
                    return;
                }

            }

        };


 

    }

}

#endif

