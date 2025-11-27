

//! \file

#ifndef Y_Protean_SoloList_Included
#define Y_Protean_SoloList_Included 1

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
        //! Solo List prototype
        /**
         CONTAINER = Dynamic<Collectable> or Sequence< Dynamic<Collectable> >
         the cache access is always behind class lock
        */
        //______________________________________________________________________
        template <
        typename NODE,
        typename CONTAINER,
        typename ThreadingPolicy>
        class SoloList :
        public ListProto<NODE,WarpedCacheOf<NODE,SingleThreadedClass>,CONTAINER,ThreadingPolicy>
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            typedef WarpedCacheOf<NODE,SingleThreadedClass>            PoolType; //!< alias
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

            //! [Container] \return capacity
            inline virtual size_t capacity() const noexcept
            {
                Y_Must_Lock();
                return list.size+pool.count();
            }

            //! [Container] \return available
            inline virtual size_t available() const noexcept
            {
                Y_Must_Lock();
                return pool.count();
            }

            //! [Container] reserve \param n number of extra objects
            inline virtual void reserve(const size_t n)
            {
                Y_Must_Lock();
                pool.cache(n);
            }

            //! [Recyclable] free content
            inline virtual void free() noexcept
            {
                this->freeList_();
            }

            //! [Releasable] release content
            inline virtual void release() noexcept {
                Y_Must_Lock();
                while(list.size>0)
                    pool.remove( list.popTail() );
                pool.release();
            }

            //! [Collectable] collect garbage \param amount amount to collect
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
            inline virtual ~SoloList() noexcept {}

        protected:
            //! setup empty
            inline explicit SoloList() : CoreType() {}

            //! duplicate \param other another list
            inline SoloList(const SoloList &other) : Container(), CoreType()
            {
                this->duplicate(other);
            }

        private:
            Y_Disable_Assign(SoloList); //!< discarding
        };
    }

}

#endif // !Y_Protean_SoloList_Included

