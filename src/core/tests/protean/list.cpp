#include "y/utest/run.hpp"
#include "y/type/args.hpp"

#include "y/memory/small/guild.hpp"
#include "y/type/destruct.hpp"

#include "y/memory/io/zombies.hpp"

#include "y/core/linked/list.hpp"
#include "y/threading/single-threaded-class.hpp"

#include "y/container.hpp"
#include "y/container/dynamic.hpp"


#include "y/protean/node/light.hpp"
#include "y/protean/node/heavy.hpp"

namespace Yttrium
{

  

    namespace Protean
    {
        template <typename NODE>
        class DirectCacheOf
        {
        public:
            typedef NODE     NodeType;
            typedef typename NodeType::ParamType ParamType;

            inline DirectCacheOf() : guild( sizeof(NODE) )
            {
                assert( guild.getBlockSize() >= sizeof(NODE) );
            }

            inline ~DirectCacheOf() noexcept
            {
            }

            inline NodeType * summon(ParamType args) {
                void * const addr = guild.acquireBlock();
                try { return new (addr) NodeType(args); }
                catch(...) { guild.releaseBlock(addr); throw; }
            }

            inline void banish(NodeType * const node) noexcept
            {
                guild.releaseBlock( Destructed(node) );
            }

            inline void remove(NodeType * const node) noexcept
            {
                banish(node);
            }

            inline NodeType * mirror(const NodeType * const node)
            {
                assert(0!=node);
                void * const addr = guild.acquireBlock();
                try { return new (addr) NodeType(*node); }
                catch(...) { guild.releaseBlock(addr); throw; }
            }

        private:
            Y_Disable_Copy_And_Assign(DirectCacheOf);
            Memory::Small::Guild guild;
        };

        template <
        typename NODE,
        typename CacheThreading>
        class WarpedCacheOf :
        public CacheThreading, public Caching
        {
        public:
            typedef NODE     NodeType;
            typedef typename NodeType::ParamType  ParamType;
            typedef typename CacheThreading::Lock Lock;

            inline WarpedCacheOf() :
            CacheThreading(),
            zpool( sizeof(NODE) )
            {
            }

            inline ~WarpedCacheOf() noexcept
            {
            }

            inline NodeType * summon(ParamType args) {
                Y_Must_Lock();
                void * const addr = zpool.query();
                try { return new (addr) NodeType(args); }
                catch(...) { zpool.store(addr); throw; }
            }

            inline void banish(NodeType * const node) noexcept
            {
                Y_Must_Lock();
                zpool.store( Destructed(node) );
            }

            inline void remove(NodeType * const node) noexcept
            {
                Y_Must_Lock();
                zpool.purge( Destructed(node) );
            }

            inline NodeType * mirror(const NodeType * const node)
            {
                Y_Must_Lock();
                assert(0!=node);
                void * const addr = zpool.query();
                try { return new (addr) NodeType(*node); }
                catch(...) { zpool.store(addr); throw; }
            }

            inline virtual void gc(const uint8_t amount) noexcept
            {
                Y_Must_Lock();
                zpool.gc(amount);
            }

            inline virtual size_t count() const noexcept
            {
                Y_Must_Lock();
                return zpool.count();
            }

            inline void cache(const size_t n)
            {
                Y_Must_Lock();
                zpool.cache(n);
            }

        private:
            Memory::Zombies zpool;
        };

        

        // Bare : releaseable, no cache
        // Solo : recyclable, releaseable, own cache
        // Coop : recyclable, releaseable, shared cache

#define Y_Protean_List_Proto() \
/**/   CONTAINER(),\
/**/   ThreadingPolicy(),\
/**/   Ingress< Core::ListOf<NODE> >(),\
/**/   list()

        template <
        typename NODE,
        typename POOL,
        typename CONTAINER,
        typename ThreadingPolicy>
        class ListProto :
        public CONTAINER,
        public ThreadingPolicy,
        public Ingress< Core::ListOf<NODE> >
        {
        public:
            typedef Core::ListOf<NODE>             ListType;
            typedef POOL                           PoolType;
            typedef Ingress<ListType>              Entrance;
            typedef typename NODE::Type            Type;
            typedef typename NODE::ConstType       ConstType;
            typedef typename NODE::ParamType       ParamType;

            typedef typename ThreadingPolicy::Lock Lock;
            inline virtual ~ListProto() noexcept { release_(); }

            inline void pushTail(ParamType args)
            {
                Y_Must_Lock();
                list.pushTail( pool.summon(args) );
            }

            inline void pushHead(ParamType args)
            {
                Y_Must_Lock();
                list.pushHead( pool.summon(args) );
            }

            inline void cutHead() noexcept
            {
                assert(list.size>0);
                Y_Must_Lock();
                pool.banish( list.popHead() );
            }

            inline void cutTail() noexcept
            {
                assert(list.size>0);
                Y_Must_Lock();
                pool.banish( list.popTail() );
            }

            virtual size_t size() const noexcept { return list.size; }



        protected:
            inline explicit ListProto() :
            Y_Protean_List_Proto(), pool()
            {}

            inline explicit ListProto(const PoolType &shared) :
            Y_Protean_List_Proto(), pool(shared)
            {}

            ListType list;
            PoolType pool;
        private:
            Y_Disable_Copy_And_Assign(ListProto);


            inline virtual typename Entrance::ConstInterface & locus() const noexcept { return list; }


        protected:
            inline void release_() noexcept {
                Y_Must_Lock();
                while(list.size>0) pool.remove( list.popTail() );
            }

            inline void duplicate(const ListProto &other)
            {
                volatile Lock primary(*this), replica(other);
                try {
                    for(const NODE *node=other->head;node;node=node->next)
                        list.pushTail( pool.mirror(node) );
                }
                catch(...) { release_(); throw; }
            }

            inline void xch(ListProto &other) noexcept
            {
                volatile Lock primary(*this), replica(other);
                list.swapListFor(other.list);
            }

        };



        template <
        typename NODE,
        typename ThreadingPolicy>
        class BareList :
        public ListProto<NODE,DirectCacheOf<NODE>,Container,ThreadingPolicy>,
        public Releasable
        {
        public:
            typedef DirectCacheOf<NODE>                                PoolType;
            typedef ListProto<NODE,PoolType,Container,ThreadingPolicy> CoreType;

            inline virtual ~BareList() noexcept {}

            inline virtual void release() noexcept { this->release_(); }

        protected:
            inline explicit BareList() : CoreType(), Releasable() {}
            inline BareList(const BareList &other) : CoreType(), Releasable()
            {
                this->duplicate(other);
            }
        private:
            Y_Disable_Assign(BareList);
        };


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

