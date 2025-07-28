
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
            template <typename MATRIX> inline
            explicit Tribes(const MATRIX &  mu,
                            const IPool &   ip,
                            QFamily::Pool & fp) :
            Tribe::List()
            {
                const size_t n = mu.rows;
                IList        bad(ip);

                // create a configuration for each row
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

                }

                // cleanup zero/duplicate rows
                finish(bad);
            }

            virtual ~Tribes() noexcept;


        private:
            Y_Disable_Copy_And_Assign(Tribes);
            bool colinearity() const noexcept;
            void finish(const IList &bad) noexcept;

        };

#if 0
        class Tribes : public Tribe::List
        {
        public:
            template <typename MATRIX>
            explicit Tribes(Tribe::Context<MATRIX> &ctx):
            Tribe::List(),
            tc(ctx.tc)
            {
                const size_t n = ctx.mu.rows;
                IList        bad(ctx.ip);

                //--------------------------------------------------------------
                //
                //
                // loop over all rows
                //
                //
                //--------------------------------------------------------------
                for(size_t first=1;first<=n;++first)
                {
                    Tribe *tr = pushTail( tc.summon(ctx,first) );

                    //----------------------------------------------------------
                    //
                    // detect zero row
                    //
                    //----------------------------------------------------------
                    if( ! tr->family->size() )
                    {
                        std::cerr << "row[" << first << "] = " << ctx.mu[first] <<  std::endl;
                        bad << first;
                        tc.banish( popTail() );
                        continue;
                    }

                    //----------------------------------------------------------
                    //
                    // detect colinear rows by unicity
                    //
                    //----------------------------------------------------------
                    if(colinearity())
                    {
                        bad << first;
                        tc.banish( popTail() );
                        continue;
                    }


#if Y_Coven_Stamp
                    //----------------------------------------------------------
                    //
                    // check stamp
                    //
                    //----------------------------------------------------------
                    const IList &stamp = tr->stamp;
                    for(const Tribe *prev=tr->prev;prev;prev=prev->prev)
                    {
                        if(prev->stamp==stamp) throw Exception("Multiple Original Stamps");
                    }
#endif

                }

                //--------------------------------------------------------------
                //
                //
                // finish
                //
                //
                //--------------------------------------------------------------
                finish(bad);
            }


            virtual ~Tribes() noexcept;

            inline size_t generate()
            {

#if 0
                {
                    Tribes heirs(ipool,tpool);
                    for(const Tribe *tr=head;tr;tr=tr->next)
                    {
                        //tr->generate(heirs,trCache);
                    }
#if Y_Coven_Stamp
                    for(const Tribe *heir=heirs.head;heir;heir=heir->next)
                    {
                        for(const Tribe *prev=heir->prev;prev;prev=prev->prev)
                        {
                            if(prev->stamp==heir->stamp) throw Exception("Multiple Inherited Stamps");
                        }
                    }
#endif
                    swapListFor(heirs);
                }

                return size;
#endif
                return 0;
            }
            
        private:
            Y_Disable_Copy_And_Assign(Tribes);
            Tribe::Cache tc;
            void finish(const IList &toRemove) noexcept;
        };

#endif

    }

}

#endif

