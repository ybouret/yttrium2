
//! \file

#ifndef Y_Cameo_Caddy_Included
#define Y_Cameo_Caddy_Included 1

#include "y/cameo/addition.hpp"
#include "y/core/linked/list/cxx.hpp"
#include "y/core/linked/pool/cxx.hpp"

namespace Yttrium
{

    namespace Cameo
    {
        //______________________________________________________________________
        //
        //
        //
        //! list of Addition<T>
        //
        //
        //______________________________________________________________________
        template <typename T>
        class Caddy :  public CxxListOf< Addition<T> >
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            typedef Addition<T>        AddType;  //!< alias
            typedef CxxListOf<AddType> ListType; //!< alias
            typedef CxxPoolOf<AddType> PoolType; //!< alias

            using ListType::size;
            using ListType::head;
            using ListType::popTail;
            using ListType::pushTail;

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup empty
            inline explicit Caddy() noexcept : ListType(), pool() {}

            //! cleanup
            inline virtual ~Caddy() noexcept {}

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! clean lists
            inline void ldz() noexcept {
                for(AddType *node=head;node;node=node->next) node->ldz();
            }

            //! prepare list \param n target
            inline void adjust(const size_t n)
            {
                while(size>n) pool.store( popTail() )->ldz();
                while(size<n) pushTail( query() );
            }

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            PoolType pool; //!< pool of alive, available AddType

        private:
            Y_Disable_Copy_And_Assign(Caddy); //!< discarding

            //! \return pooled or new AddType
            AddType *query()
            {
                return pool.size ? pool.query() : new AddType();
            }
        };

    }

}

#endif // !Y_Cameo_Caddy_Included
