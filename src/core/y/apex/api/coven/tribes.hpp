
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

        class Tribes : public Tribe::List
        {
        public:
            static const unsigned NoReplica = 0x01;

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

                    if(!tribe->family)
                    {
                        std::cerr << "mu[" << first << "] = " << mu[first] << std::endl;
                        delete popTail();
                        bad << first;
                        continue;
                    }

                    if(colinearity())
                    {
                        delete popTail();
                        bad << first;
                        continue;
                    }

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

            virtual ~Tribes() noexcept;

            friend std::ostream & operator<<(std::ostream &, const Tribes &);


            template <typename MATRIX> inline
            size_t generate(const MATRIX & mu,
                            Survey * const survey,
                            const unsigned strategy)
            {
                {
                    Tribe::List heirs;
                    for(Tribe *tribe=head;tribe;tribe=tribe->next)
                    {
                        tribe->generate(heirs,mu,survey);
                    }
                    swapListFor(heirs);
                }


                if( 0 != (strategy&NoReplica) )
                {
                    makeNoReplica();
#if 1
                    for(const Tribe *curr=head;curr;curr=curr->next)
                    {
                        for(const Tribe *prev=curr->prev;prev;prev=prev->prev)
                        {
                            if( !(curr->basis == prev->basis) && __Zero__ == QFamily::Compare(curr->family,prev->family) )
                            {
                                std::cerr << "---> same families!!" << std::endl;
                                std::cerr << *curr << std::endl;
                                std::cerr << *prev << std::endl;
                            }
                        }
                    }
#endif
                }




                return size;
            }


        private:
            Y_Disable_Copy_And_Assign(Tribes);
            bool colinearity() const noexcept;
            void finish(const IList &bad) noexcept;
            void makeNoReplica();

        };


    }

}

#endif

