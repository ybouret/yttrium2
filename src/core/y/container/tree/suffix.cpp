
#include "y/container/tree/suffix.hpp"
#include "y/stream/output.hpp"

namespace Yttrium
{


    SuffixTree::Node:: Node() noexcept :
    Object(),
    code(0),
    addr(0),
    sire(0),
    chld(),
    next(0),
    prev(0)
    {
    }

    SuffixTree::Node:: ~Node() noexcept
    {

    }

    bool SuffixTree::Node:: descendsFrom(const Node * const root) const noexcept
    {
        assert(0!=root);
        const Node * node = this;
        while(node->sire)
            node=node->sire;
        return root == node;
    }

    OutputStream &  SuffixTree::Node:: viz(OutputStream &fp) const
    {
        nodeName(fp) << '[';
        if(addr) fp << "shape=circle,style=bold";
        else     fp << "shape=square";
        fp << ',';
        if(code<256)
        {
            Label(fp,char(code));
        }
        else
        {
            Label(fp,"???");
        }

        Endl(fp << ']');
        for(const Node *node=chld.head;node;node=node->next)
        {
            node->viz(fp);
            Endl(to(node,fp));
        }
        return fp;
    }


}

namespace Yttrium
{


    SuffixTree:: SuffixTree():
    size(0),
    root( new Node() ),
    pool()
    {

    }

    SuffixTree:: ~SuffixTree() noexcept
    {
        assert(size<=0);
        assert(0!=root);
        delete root; Coerce(root) = 0;
    }

    SuffixTree::Node * SuffixTree:: create(Node * const sire,
                                           const code_t code)
    {
        Node * const node = pool.size ? pool.query() : new Node();

        Coerce(node->sire) = sire;
        Coerce(node->code) = code;
        Coerce(node->addr) = 0;

        return node;
    }


    void SuffixTree:: prune(Node * node) noexcept
    {
        assert(0!=node);
        assert(0==node->addr);

    PRUNE:
        if(0==node->chld.size && root != node)
        {
            // is a leave
            Node * const sire = node->sire;
            assert(sire);
            assert(sire->chld.owns(node));
            pool.store(sire->chld.pop(node));
            node = sire;
            if(node->addr) return;
            goto PRUNE;
        }

    }

    OutputStream & SuffixTree:: viz(OutputStream &fp) const
    {
        return root->viz(fp);
    }

    void SuffixTree:: free() noexcept
    {
        clear();
    }

    void SuffixTree:: release() noexcept
    {
        purge();
    }


    void SuffixTree:: clear() noexcept
    {
        clear(root);
        Coerce(size)=0;
    }

    void SuffixTree:: clear(Node *node) noexcept
    {
        assert(0!=node);

        Coerce(node->sire) = 0;
        Coerce(node->code) = 0;
        Coerce(node->addr) = 0;

        Node::List &list = node->chld;
        while(list.size)
            clear( list.popTail() );

        if(root!=node)
            pool.store(node);
    }

    void SuffixTree:: purge() noexcept
    {
        assert(root);
        Coerce(size) = 0;
        pool.release();
        Coerce(root->sire) = 0;
        Coerce(root->code) = 0;
        Coerce(root->addr) = 0;
        root->chld.release();

    }



    void SuffixTree:: remove(Node * const node) noexcept
    {
        assert(0!=node);
        assert(0!=node->addr);
        assert(node->descendsFrom(root));
        Coerce(node->addr) = 0;
        --Coerce(size);
        prune(node);
    }

}

#include "y/core/linked/convert/pool-to-ordered-list.hpp"
#include "y/core/linked/convert/list-to-pool.hpp"

namespace Yttrium
{

    void SuffixTree:: gc(const uint8_t amount) noexcept
    {
        Node::List list;
        Core::PoolToOrderedList::Convert(list,pool);
        const size_t newSize = NewSize(amount,list.size);
        while(list.size>newSize) delete list.popTail();
        Core::ListToPool::Convert(pool,list);
    }


}
