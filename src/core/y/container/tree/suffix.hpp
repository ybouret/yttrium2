//! \file

#ifndef Y_SuffixTree_Included
#define Y_SuffixTree_Included 1

#include "y/core/linked/list/cxx.hpp"
#include "y/core/linked/pool/cxx.hpp"
#include "y/object.hpp"
#include "y/graphviz/vizible.hpp"


namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //! Agnostic Suffix Tree
    //
    //
    //__________________________________________________________________________
    class SuffixTree
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        typedef uint64_t code_t; //!< alias

        //______________________________________________________________________
        //
        //
        //! internal node
        //
        //______________________________________________________________________
        class Node : public Object, public Vizible
        {
        public:
            //__________________________________________________________________
            //
            // Definitions
            //__________________________________________________________________
            typedef CxxListOf<Node> List; //!< alias
            typedef CxxPoolOf<Node> Pool; //!< alias

            //__________________________________________________________________
            //
            // C++
            //__________________________________________________________________
            explicit Node() noexcept; //!< setup clear
            virtual ~Node() noexcept; //!< cleanup

            //__________________________________________________________________
            //
            // Methods
            //__________________________________________________________________
            OutputStream & viz(OutputStream &) const; //!< emit graphViz \return output stream

            //__________________________________________________________________
            //
            // Members
            //__________________________________________________________________
            const code_t code; //!< current code
            void * const addr; //!< user's data address
            Node * const sire; //!< parent
            List         chld; //!< child[ren]
            Node *       next; //!< for list/pool
            Node *       prev; //!< for pool

        private:
            Y_Disable_Copy_And_Assign(Node); //!< discarding
        };

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
        explicit SuffixTree();          //!< setup with root
        virtual ~SuffixTree() noexcept; //!< cleanup

        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________

        //! search node with given path
        /**
         \param path path iterator
         \param plen path length
         \return node at given path, NULL otherwise
         */
        template <typename ITERATOR> inline
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

        //! search node with given path and caching
        /**
         \param path path iterator
         \param plen path length
         \return node at given path, NULL otherwise
         */
        template <typename ITERATOR> inline
        Node * search(ITERATOR path,
                      size_t   plen)   noexcept
        {
            assert(0!=root);
            Node * node = root;
            while(plen-- > 0)
            {
                const code_t code = static_cast<code_t>( *(path++) );
                bool         walk = false;
                for( Node *chld=node->chld.head;chld;chld=chld->next)
                {
                    if(code == chld->code)
                    {
                        node->chld.moveToFront(chld);
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



        //! insert address at given path
        /**
         \param path path iterator
         \param plen path length
         \param addr addr!=NULL to store into tree
         \return found/new node or NULL if node was occupied
         */
        template <typename ITERATOR> inline
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


        //! remove address from tree
        /**
         tree if pruned upon success
         \param path path iterator
         \param plen path length
         \return found address at given path, NULL if not found
         */
        template <typename ITERATOR> inline
        void * remove(ITERATOR     path,
                      size_t       plen) noexcept
        {
            Node * const node = (Node *) search(path,plen);
            if(!node) return 0;
            void * const addr = node->addr;
            Coerce(node->addr) = 0;
            --Coerce(size);
            prune(node);
            return addr;
        }


        //! emit graphViz \return output stream
        OutputStream & viz(OutputStream &) const;

        //______________________________________________________________________
        //
        //
        // Members
        //
        //______________________________________________________________________
        const size_t size; //!< keep trace of inserted data
    private:
        Node * const root; //!< fixed root for zero-length path
        Node::Pool   pool; //!< pool of nodes

        Y_Disable_Copy_And_Assign(SuffixTree); //!< discarding

        //! create a node with parent and value
        /**
         \param sire parent node
         \param code code value
         \return new/stored node
         */
        Node *       create(Node * const sire,
                            const code_t code);

        //! try to prune the tree from clean node
        void         prune(Node *) noexcept;
    };



}

#endif
