
#include "y/container/htable.hpp"
#include "y/object/school-of.hpp"
#include "y/memory/operating.hpp"
#include "y/calculus/base2.hpp"
#include "y/system/exception.hpp"
#include "y/type/destroy.hpp"
#include "y/core/utils.hpp"

namespace Yttrium
{
    const char * const HTable:: CallSign = "HTable";

    class HTable:: Code :
    public Object,
    public Memory::SchoolOf<Slot>,
    public Memory::Operating<Slot>
    {
    public:

        explicit Code(const size_t n) :
        Object(),
        Memory::SchoolOf<Slot>(n),
        Memory::Operating<Slot>(entry,n),
        mask(n-1)
        {
            assert( IsPowerOfTwo(n) );
            assert(n==numBlocks);
        }

        virtual ~Code() noexcept
        {
        }


        static Code * createFor(const size_t nmin)
        {
            if(nmin>Base2<size_t>::MaxBytes)
                throw Specific::Exception(CallSign,"table size overflow");
            return new Code( NextPowerOfTwo(nmin) );
        }

        inline void free(Node::Pool &pool) noexcept
        {
            for(size_t i=0;i<numBlocks;++i)
            {
                Slot &slot = entry[i];
                while(slot.size) pool.store( slot.popTail() )->clear();
            }
        }

        inline bool isFree() const noexcept
        {
            for(size_t i=0;i<numBlocks;++i)
            {
                if(entry[i].size) return false;
            }
            return true;
        }

        inline void steal(Code &source) noexcept
        {
            assert(isFree());
            for(size_t i=0;i<source.numBlocks;++i)
            {
                Slot &src = source.entry[i];
                while(src.size)
                {
                    Node * const node = src.popHead();
                    entry[node->hkey&mask].pushTail(node);
                }
            }
            assert(source.isFree());
        }

        inline void release() noexcept
        {
            for(size_t i=0;i<numBlocks;++i)
                entry[i].release();
        }


        const size_t mask;


    private:
        Y_Disable_Copy_And_Assign(Code);
    };


    HTable:: Node:: ~Node() noexcept
    {

    }

    HTable:: Node:: Node() noexcept :
    Object(), hkey(0), data(0),next(0), prev(0)
    {}


    void HTable:: Node:: clear() noexcept
    {
        Coerce(hkey) = 0;
        Coerce(data) = 0;
    }


    HTable:: ~HTable() noexcept
    {
        assert(0!=code);
        assert(0==size);
        Destroy(code);
    }


    HTable:: HTable(const size_t minSlots) :
    size(0),
    code( new Code( Max<size_t>(4,minSlots) ) ),
    pool()
    {

    }



    const HTable:: Node * HTable:: search(const size_t       hkey,
                                          const void * const data,
                                          Same const         same) const
    {
        assert(code);
        assert(same);
        const Slot * const slot = & code->entry[hkey&code->mask];
        for(const Node *node=slot->head;node;node=node->next)
        {
            if(hkey == node->hkey && same(data,node->data) )
            {
                return node;
            }
        }
        return 0;
    }

    HTable::Node * HTable:: search(const size_t       hkey,
                                   const void * const data,
                                   Same const         same,
                                   Slot *   &         slot)
    {
        assert(code);
        assert(same);
        slot = & code->entry[hkey&code->mask];
        for(Node *node=slot->head;node;node=node->next)
        {
            if(hkey == node->hkey && same(data,node->data) )
            {
                return slot->moveToFront(node);
            }
        }
        return 0;
    }


    HTable::Node  * HTable:: insert(const size_t hkey,
                                    void * const data,
                                    Same   const same)
    {
        assert(code);
        assert(same);
        Slot * slot = 0;
        if( search(hkey,data,same,slot) ) return 0;
        Node * const node = slot->pushHead(pool.size ? pool.query() : new Node());
        Coerce(node->hkey) = hkey;
        Coerce(node->data) = data;
        ++Coerce(size);

        // check load factor
        if(size/code->numBlocks>MaxLoadFactor)
        {
            Code * temp = Code::createFor(code->numBlocks<<1);
            temp->steal(*code);
            delete code;
            code = temp;
        }
        return node;
    }


    void HTable:: remove(Node * const node) noexcept
    {
        assert(0!=node);
        assert(0!=code);
        Slot &slot = code->entry[node->hkey&code->mask];
        assert(slot.owns(node));
        pool.store( slot.pop(node) )->clear();
        --Coerce(size);
    }


    void * HTable::remove(const size_t       hkey,
                          const void * const data,
                          Same const         same)
    {
        assert(code);
        assert(same);
        Slot *       slot = 0;
        Node * const node = search(hkey,data,same,slot);

        if(!node) return 0;

        void * const res = node->data;
        assert(node==slot->head);
        pool.store( slot->popHead() )->clear();
        --Coerce(size);
        return res;
    }

    void HTable:: free() noexcept
    {
        assert(code);
        code->free(pool);
        assert(code->isFree());
        Coerce(size)=0;
    }

    void HTable:: release() noexcept
    {
        assert(code);
        code->release();
        pool.release();
        Coerce(size)=0;
    }

}

#include "y/core/linked/convert/pool-to-ordered-list.hpp"
#include "y/core/linked/convert/list-to-pool.hpp"

namespace Yttrium
{
    void HTable:: gc(const uint8_t amount) noexcept
    {
        Node::List list;
        Core::PoolToOrderedList::Convert(list,pool);
        const size_t newSize = NewSize(amount,list.size);
        while(list.size>newSize) delete list.popTail();
        Core::ListToPool::Convert(pool,list);
    }

}
