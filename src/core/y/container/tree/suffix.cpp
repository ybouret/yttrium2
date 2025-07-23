
#include "y/container/tree/suffix.hpp"

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


        void SuffixTree:: prune(Node *const node) noexcept
        {

        }
    }


}
