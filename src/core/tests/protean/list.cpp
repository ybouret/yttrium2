#include "y/utest/run.hpp"
#include "y/type/args.hpp"

#include "y/memory/small/guild.hpp"
#include "y/type/destruct.hpp"

namespace Yttrium
{

    namespace Protean
    {
        template <typename T>
        class LightNode
        {
        public:
            Y_ARGS_EXPOSE(T,Type);
            typedef ConstType & ParamType;

            inline LightNode(ParamType arg) noexcept :
            next(0), prev(0), data( (MutableType &)arg )
            {
            }

            inline ~LightNode() noexcept {}

            inline LightNode(const LightNode &node) noexcept :
            next(0), prev(0), data(node.data)
            {
            }

            inline Type &      operator*()       noexcept { return data; }
            inline ConstType & operator*() const noexcept { return data; }


            LightNode * next;
            LightNode * prev;
        private:
            MutableType &data;
            Y_Disable_Assign(LightNode);
        };

        template <typename T>
        class HeavyNode
        {
        public:
            Y_ARGS_DECL(T,Type);

            inline HeavyNode(ParamType arg) noexcept :
            next(0), prev(0), data(arg)
            {
            }

            inline ~HeavyNode() noexcept {}

            inline HeavyNode(const HeavyNode &node)  :
            next(0), prev(0), data(node.data)
            {
            }

            inline Type &      operator*()       noexcept { return data; }
            inline ConstType & operator*() const noexcept { return data; }


            HeavyNode * next;
            HeavyNode * prev;
        private:
            MutableType data;
            Y_Disable_Assign(HeavyNode);
        };

        template <typename NODE>
        class NoCache
        {
        public:
            typedef NODE     NodeType;
            typedef typename NodeType::ParamType ParamType;

            inline NoCache() : guild( sizeof(NODE) )
            {
                assert( guild.getBlockSize() >= sizeof(NODE) );
            }

            inline ~NoCache() noexcept
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

            inline NodeType * mirror(const NodeType * const node)
            {
                assert(0!=node);
                void * const addr = guild.acquireBlock();
                try { return new (addr) NodeType(*node); }
                catch(...) { guild.releaseBlock(addr); throw; }
            }




        private:
            Y_Disable_Copy_And_Assign(NoCache);
            Memory::Small::Guild guild;
        };

        // Base : releaseable, no cache
        // Solo : recyclable, releaseable, own cache
        // Coop : recyclable, releaseable, shared cache



    }

}


using namespace Yttrium;



Y_UTEST(protean_list)
{

    typedef Protean::HeavyNode<int> HNode;

    Protean::NoCache<HNode> no_cache;

    HNode *node = no_cache.summon(3);
    std::cerr << **node << std::endl;
    HNode *replica = no_cache.mirror(node);
    Y_ASSERT(**replica==**node);
    no_cache.banish(node);
    no_cache.banish(replica);
}
Y_UDONE()

