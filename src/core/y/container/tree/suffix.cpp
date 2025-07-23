
#include "y/container/tree/suffix.hpp"
#include "y/stream/output.hpp"

namespace Yttrium
{

    namespace Core
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

        OutputStream &  SuffixTree::Node:: viz(OutputStream &fp) const
        {
            name(fp) << '[';
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

}

namespace Yttrium
{

    namespace Core
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
                goto PRUNE;
            }

        }

        OutputStream & SuffixTree:: viz(OutputStream &fp) const
        {
            return root->viz(fp);
        }


    }


}
