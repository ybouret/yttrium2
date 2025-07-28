
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
            stamp(ip),
            fpool(fp),
            family( fpool.start(mu[first]) )
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
        };


 

    }

}

#endif

