//! \file

#ifndef Y_SuffixTree_Included
#define Y_SuffuxTree_Included 1

#include "y/core/linked/list/cxx.hpp"
#include "y/core/linked/pool/cxx.hpp"
#include "y/object.hpp"


namespace Yttrium
{

    namespace Core
    {


        class SuffixTree
        {
        public:
            typedef uint64_t code_t;

            class Node : public Object
            {
            public:
                typedef CxxListOf<Node> List;
                typedef CxxPoolOf<Node> Pool;

                explicit Node() noexcept;
                virtual ~Node() noexcept;

                const code_t code;
                void * const addr; //!< user's data address
                Node * const sire; //!< parent
                List         chld; //!< child[ren]
                Node *       next;
                Node *       prev;
            private:
                Y_Disable_Copy_And_Assign(Node);
            };

            explicit SuffixTree();
            virtual ~SuffixTree() noexcept;

            template <typename ITERATOR>
            const Node * search(ITERATOR path,
                                size_t   plen) const noexcept
            {
                assert(0!=root);
                const Node * node = root;
                while(plen-- > 0)
                {
                    const code_t code = static_cast<code_t>( *(path++) );
                    bool         walk = false;
                    for(const Node *chld=node->chld.head;chld;chld=chld->next)
                    {
                        if(code == chld->code)
                        {
                            node = chld;
                            walk = true;
                            break;
                        }
                    }
                    if(!walk) return 0;
                    assert(0!=node);
                }
                return node;
            }

            template <typename ITERATOR>
            Node * insert(ITERATOR     path,
                          size_t       plen,
                          void * const addr)
            {
                assert(0!=addr);

                // walk/create tree
                Node * node = root;
                while(plen-- > 0)
                {
                    const code_t code = static_cast<code_t>( *(path++) );
                    bool         walk = false;
                    Node::List  &list = node->chld;
                    for(Node *chld=list.head;chld;chld=chld->next)
                    {
                        if(code == chld->code)
                        {
                            node = chld;
                            list.moveToFront(chld);
                            walk = true;
                            break;
                        }
                    }
                    if(!walk)
                        node = list.pushHead(create(node,code));
                }

                if(node->addr)
                {
                    return 0; // occupied
                }
                else
                {
                    Coerce(node->addr) = addr;
                    ++Coerce(size);
                    return node;
                }
            }

            template <typename ITERATOR>
            void * remove(ITERATOR     path,
                          size_t       plen)
            {
                Node * const node = (Node *) search(path,plen);
                if(!node) return 0;
                void * const addr = node->addr;
                Coerce(node->addr) = 0;
                --Coerce(size);
                prune(node);
                return addr;
            }


            const size_t size; //!< keep trace of inserted data
        private:
            Y_Disable_Copy_And_Assign(SuffixTree);
            Node * const root;
            Node::Pool   pool;
            Node *       create(Node * const sire,
                                const code_t code);
            void         prune(Node * const node) noexcept;
        };


    }


}

#endif
