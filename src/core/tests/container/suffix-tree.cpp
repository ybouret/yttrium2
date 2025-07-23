#include "y/container/tree/suffix.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(container_suffix_tree)
{

    Core::SuffixTree tree;

    {
        int a = 2;
        const char * const key = "Hello";
        Core::SuffixTree::Node * node = tree.insert(key,3,&a);
        Y_ASSERT(0!=node);
        Y_ASSERT(&a==node->addr);
        Y_ASSERT(tree.search(key,3) == node);
        Coerce(tree.size) = 0;
    }


}
Y_UDONE()


