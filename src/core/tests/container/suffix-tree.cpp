#include "y/container/tree/suffix.hpp"
#include "y/utest/run.hpp"
#include "y/stream/libc/output.hpp"
#include <cstring>

using namespace Yttrium;

Y_UTEST(container_suffix_tree)
{

    Core::SuffixTree tree;

    {
        int a = 2;
        int b = 3;
        int c = 4;
        int d = 5;
        const char * const key = "Hello";
        Core::SuffixTree::Node * node = tree.insert(key,3,&a);
        Vizible::Render("tree1.dot", tree);
        tree.insert(key,2,&b);
        Vizible::Render("tree2.dot", tree);
        tree.insert(key,5,&c);
        Vizible::Render("tree3.dot", tree);

        const char * const key2 = "Helico";
        tree.insert(key2,strlen(key2),&d);
        Vizible::Render("tree4.dot", tree);



        Y_ASSERT(0!=node);
        Y_ASSERT(&a==node->addr);
        Y_ASSERT(tree.search(key,3) == node);


        Y_ASSERT( &b == tree.remove(key,2) );
        Vizible::Render("tree5.dot", tree);

        Y_ASSERT( &d == tree.remove(key2,strlen(key2)) );
        Vizible::Render("tree6.dot", tree);

        Y_ASSERT( &a == tree.remove(key,3) );
        Vizible::Render("tree7.dot", tree);

        Y_ASSERT( &c == tree.remove(key,5) );
        Vizible::Render("tree8.dot", tree);

        Y_ASSERT(0==tree.size);

    }


}
Y_UDONE()


