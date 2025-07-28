
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
            static const unsigned DitchReplicae = 0x01;
            static const unsigned GroupFamilies = 0x02;

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
                follow(strategy);
                return size;
            }


        private:
            Y_Disable_Copy_And_Assign(Tribes);
            bool colinearity() const noexcept;
            void finish(const IList &bad) noexcept;
            void follow(const unsigned strategy);

            void makeDitchReplicae();
            void makeGroupFamilies();
        };


    }

}

#endif

