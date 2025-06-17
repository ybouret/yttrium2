#include "y/utest/run.hpp"
#include "y/type/args.hpp"

#include "y/memory/small/guild.hpp"
#include "y/type/destruct.hpp"

#include "y/memory/io/zombies.hpp"

#include "y/core/linked/list.hpp"
#include "y/threading/single-threaded-class.hpp"

//#include "y/container.hpp"

#include "y/protean/bare/list.hpp"

#include "y/protean/cache/direct.hpp"
#include "y/protean/cache/warped.hpp"
#include "y/protean/node/light.hpp"
#include "y/protean/node/heavy.hpp"

#include "y/container/dynamic.hpp"

namespace Yttrium
{

  

    namespace Protean
    {
        
        // Bare : releaseable, no cache
        // Solo : recyclable, releaseable, own cache
        // Coop : recyclable, releaseable, shared cache







        template <typename T, typename ThreadingPolicy = SingleThreadedClass>
        class LightBareList : public BareList<LightNode<T>,ThreadingPolicy>
        {
        public:
            typedef LightNode<T>                       NodeType;
            typedef BareList<NodeType,ThreadingPolicy> BaseType;
            typedef typename BaseType::Lock            Lock;

            inline explicit LightBareList() : BaseType() {}
            inline virtual ~LightBareList() noexcept {}
            inline LightBareList(const LightBareList &other) : BaseType(other)
            {
            }

        private:
            Y_Disable_Assign(LightBareList);

        };

        template <typename T, typename ThreadingPolicy = SingleThreadedClass>
        class HeavyBareList : public BareList<HeavyNode<T>,ThreadingPolicy>
        {
        public:
            typedef HeavyNode<T>                       NodeType;
            typedef BareList<NodeType,ThreadingPolicy> BaseType;

            inline explicit HeavyBareList() : BaseType() {}
            inline virtual ~HeavyBareList() noexcept {}
            inline HeavyBareList(const HeavyBareList &other) : BaseType(other)
            {
            }

        private:
            Y_Disable_Assign(HeavyBareList);
        };


        typedef Dynamic<Collectable> BaseContainer;

        // the cache access is always behind class lock
        template <
        typename NODE,
        typename ThreadingPolicy>
        class SoloList :
        public ListProto<NODE,WarpedCacheOf<NODE,SingleThreadedClass>,BaseContainer,ThreadingPolicy>
        {
        public:
            typedef WarpedCacheOf<NODE,SingleThreadedClass>                   PoolType;
            typedef ListProto<NODE,PoolType,BaseContainer,ThreadingPolicy> CoreType;
            using CoreType::pool;
            using CoreType::list;
            typedef typename CoreType::Lock Lock;


            inline virtual ~SoloList() noexcept {}

            inline virtual size_t capacity() const noexcept
            {
                Y_Must_Lock();
                return list.size+pool.count();
            }

            inline virtual size_t available() const noexcept
            {
                Y_Must_Lock();
                return pool.count();
            }

            inline virtual void reserve(const size_t n)
            {
                Y_Must_Lock();
                pool.cache(n);
            }

            inline virtual void free() noexcept
            {
                Y_Must_Lock();
                while(list.size>0)
                    pool.banish( list.popTail() );
            }

            inline virtual void release() noexcept { this->release_(); }

            inline virtual void gc(const uint8_t amount) noexcept
            {
                Y_Must_Lock();
                pool.gc(amount);
            }

        protected:
            inline explicit SoloList() : CoreType() {}
            inline SoloList(const SoloList &other) : CoreType()
            {
                this->duplicate(other);
            }
        private:
            Y_Disable_Assign(SoloList);
        };

        template <typename T, typename ThreadingPolicy = SingleThreadedClass>
        class HeavySoloList : public SoloList<HeavyNode<T>,ThreadingPolicy>
        {
        public:
            typedef HeavyNode<T>                       NodeType;
            typedef SoloList<NodeType,ThreadingPolicy> BaseType;

            inline explicit HeavySoloList() : BaseType() {}
            inline virtual ~HeavySoloList() noexcept {}
            inline HeavySoloList(const HeavySoloList &other) : BaseType(other)
            {
            }

        private:
            Y_Disable_Assign(HeavySoloList);
        };


        template <typename T, typename ThreadingPolicy = SingleThreadedClass>
        class LightSoloList : public SoloList<LightNode<T>,ThreadingPolicy>
        {
        public:
            typedef LightNode<T>                       NodeType;
            typedef SoloList<NodeType,ThreadingPolicy> BaseType;

            inline explicit LightSoloList() : BaseType() {}
            inline virtual ~LightSoloList() noexcept {}
            inline LightSoloList(const LightSoloList &other) : BaseType(other)
            {
            }

        private:
            Y_Disable_Assign(LightSoloList);
        };



    }

}


using namespace Yttrium;



Y_UTEST(protean_list)
{

    {
        typedef Protean::HeavyNode<int> HNode;
        Protean::DirectCacheOf<HNode> no_cache;
        HNode *node = no_cache.summon(3);
        std::cerr << **node << std::endl;
        HNode *replica = no_cache.mirror(node);
        Y_ASSERT(**replica==**node);
        no_cache.banish(node);
        no_cache.banish(replica);
    }

    int arr[3] = { 1, 2, 3 };
    
    {
        Protean::LightBareList<int> lb;
        Protean::HeavyBareList<int> hb;


        lb.pushTail(arr[0]);
        lb.pushTail(arr[1]);
        std::cerr << lb << std::endl;

        hb.pushTail(1);
        hb.pushHead(2);
        std::cerr << hb << std::endl;
    }

    {
        Protean::HeavySoloList<int> hb;

    }


}
Y_UDONE()

