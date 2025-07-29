
//! \file

#ifndef Y_Coven_Tribes_Included
#define Y_Coven_Tribes_Included 1

#include "y/apex/api/coven/tribe.hpp"
#if Y_Coven_Stamp
#include "y/exception.hpp"
#endif

namespace Yttrium
{

    namespace Coven
    {

        //______________________________________________________________________
        //
        //
        //
        //! Tribes from successive generations
        //
        //
        //______________________________________________________________________
        class Tribes : public Tribe::List
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const unsigned EndEarlyBasis = 0x01; //!< won't produce
            static const unsigned DitchReplicae = 0x02; //!< no same basis+ready
            static const unsigned GroupFamilies = 0x04; //!< group similar families
            static const unsigned UseHyperPlane = 0x08; //!< optimize last search

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! prepare root tribes
            /**
             \param mu size=mu.rows, dims=mu.cols
             \param ip shared index pool
             \param fp persistent family pool, fp.dimensions = mu.cols
             \param survey optional survey to take on root vectors
             */
            template <typename MATRIX> inline
            explicit Tribes(const MATRIX &  mu,
                            const IPool &   ip,
                            QFamily::Pool & fp,
                            Survey * const  survey) :
            Tribe::List()
            {
                const size_t n = mu.rows;
                IList        bad(ip);

                //--------------------------------------------------------------
                //
                //
                // create a configuration for each row
                //
                //
                //--------------------------------------------------------------
                for(size_t first=1;first<=n;++first)
                {
                    Tribe *tribe = pushTail( new Tribe(mu,first,ip,fp) );

                    //----------------------------------------------------------
                    //
                    // zero row
                    //
                    //----------------------------------------------------------
                    if(!tribe->family)
                    {
                        std::cerr << "mu[" << first << "] = " << mu[first] << std::endl;
                        delete popTail();
                        bad << first;
                        continue;
                    }

                    //----------------------------------------------------------
                    //
                    // colinear row (detected by unicity)
                    //
                    //----------------------------------------------------------
                    if(colinearity())
                    {
                        delete popTail();
                        bad << first;
                        continue;
                    }

                    //----------------------------------------------------------
                    //
                    // collect
                    //
                    //----------------------------------------------------------
                    if(survey) {
                        survey->collect(*(tribe->family->lastVec));
                    }
                }

                //--------------------------------------------------------------
                //
                // cleanup zero/duplicate rows
                //
                //--------------------------------------------------------------
                finish(bad);
                sort(Tribe::Compare);
            }

            //! cleanup
            virtual ~Tribes() noexcept;

            //! display
            friend std::ostream & operator<<(std::ostream &, const Tribes &);


            //! produce next generation
            /**
             \param mu       original matrix
             \param survey   optional survey to take on newly created vectors
             \param strategy strateg[y|ies] to follow
             \return number of new tribes
             */
            template <typename MATRIX> inline
            size_t generate(const MATRIX & mu,
                            Survey * const survey,
                            const bool     optimize)
            {
                {
                    Tribe::List heirs;
                    for(Tribe *tribe=head;tribe;tribe=tribe->next)
                    {
                        tribe->generate(heirs,mu,survey,optimize);
                    }
                    swapListFor(heirs);
                }
                if(optimize)
                    shrink(); // remove tribes that won't produce new vectors
                return size;
            }


        private:
            Y_Disable_Copy_And_Assign(Tribes); //!< cleanup

            bool colinearity() const noexcept;    //!< \return colinear last vector
            void finish(const IList & ) noexcept; //!< remove bad indices from all root trubes
            void follow(const unsigned);          //!< call optimization
            void shrink();

            void makeEndEarlyBasis() noexcept; //!< apply EndEarlyBasis
            void makeDitchReplicae() noexcept; //!< apply DitchReplicae
            void makeGroupFamilies();          //!< apply GroupFamilies
        };


    }

}

#endif

