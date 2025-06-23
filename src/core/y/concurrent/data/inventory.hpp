
//! \file

#ifndef Y_Concurrent_Inventory_Included
#define Y_Concurrent_Inventory_Included 1

#include "y/protean/cache/warped.hpp"
#include "y/singleton.hpp"
#include "y/threading/multi-threaded-handle.hpp"
#include "y/xml/attribute.hpp"

namespace Yttrium
{

    namespace Concurrent
    {
        template <typename T>
        class Inventory : public Singleton<Inventory<T>, ClassLockPolicy>,
        public Protean::WarpedCacheOf<T,MultiThreadedHandle>
        {
        public:
            static const System::AtExit::Longevity LifeTime = T::LifeTime;
            static const char * const              CallSign;

            typedef Singleton<Inventory<T>, ClassLockPolicy>      ClassType;
            typedef Protean::WarpedCacheOf<T,MultiThreadedHandle> CacheType;
            using ClassType::access;


            virtual void display(std::ostream &os,size_t indent) const
            {
                this->initProlog(os,indent);
                const size_t in_cache = this->count();
                os << Y_XML_Attr(in_cache);
                this->initEpilog(os,true);
            }

        private:
            Y_Disable_Copy_And_Assign(Inventory);
            friend class Singleton<Inventory<T>, ClassLockPolicy>;

            explicit Inventory() : ClassType(), CacheType(access) {}
            virtual ~Inventory() noexcept {}
        };

        template <typename T>
        const char * const Inventory<T>::CallSign = T::CallSign;
    }

}

#endif

