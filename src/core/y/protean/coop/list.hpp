


//! \file

#ifndef Y_Protean_CoopList_Included
#define Y_Protean_CoopList_Included 1

#include "y/protean/proto/list.hpp"
#include "y/protean/cache/warped.hpp"
#include "y/threading/single-threaded-class.hpp"
#include "y/protean/common-container.hpp"

namespace Yttrium
{
    namespace Protean
    {

        //______________________________________________________________________
        //
        //
        //
        //! List with shared cache
        /** CONTAINER = Dynamic<Collectable> or Sequence< Dynamic<Collectable> >
         the cache access is NOT always behind class lock
         */
        //______________________________________________________________________
        template <
        typename NODE,
        typename CONTAINER,
        typename ThreadingPolicy>
        class CoopList : public ListProto<NODE,WarpedCacheOf<NODE,ThreadingPolicy>,CONTAINER,ThreadingPolicy>
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            typedef WarpedCacheOf<NODE,ThreadingPolicy>                PoolType; //!< alias
            typedef ListProto<NODE,PoolType,CONTAINER,ThreadingPolicy> CoreType; //!< alias
            typedef typename CoreType::Lock                            Lock;     //!< alias
            using CoreType::pool;
            using CoreType::list;



            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________

            //! \return total capacity
            inline virtual size_t capacity() const noexcept
            {
                Y_Must_Lock();
                return list.size+pool.count();
            }

            //! \return available in shared pool
            inline virtual size_t available() const noexcept
            {
                Y_Must_Lock();
                return pool.count();
            }

            //! grow shared pool \param n items to reserve
            inline virtual void reserve(const size_t n)
            {
                Y_Must_Lock();
                pool.cache(n);
            }

            //! free content, keep memory
            inline virtual void free() noexcept
            {
                free_();
            }

            //! free content
            inline virtual void release() noexcept { free_(); }

            //! collect garbage \param amount amount to collect
            inline virtual void gc(const uint8_t amount) noexcept
            {
                Y_Must_Lock();
                pool.gc(amount);
            }


            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! cleanup
            inline virtual ~CoopList() noexcept {}
        protected:

            //! setup \param shared shared pool
            inline explicit CoopList(const PoolType &shared) : CoreType(shared) {}

            //! duplicate with same cache \param other another list
            inline CoopList(const CoopList &other) : Container(), CoreType(other.pool)
            {
                this->duplicate(other);
            }

        private:
            Y_Disable_Assign(CoopList); //!< discarding

            inline void free_() noexcept
            {
                Y_Must_Lock();
                while(list.size>0)
                    pool.banish( list.popTail() );
            }
        };
    }

}

#endif

