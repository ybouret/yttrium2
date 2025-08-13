
//! \file

#ifndef Y_Jive_Syntax_InternalNode_Included
#define Y_Jive_Syntax_InternalNode_Included 1

#include "y/jive/syntax/node.hpp"

namespace Yttrium
{
    namespace Jive
    {

        namespace Syntax
        {
            //__________________________________________________________________
            //
            //
            //
            //! Internal node
            //
            //
            //__________________________________________________________________
            class InternalNode : public Node, public NodeList
            {
                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
            private:
                //! setup with internal rule
                explicit InternalNode(const Internal &) noexcept;

            public:
                //! cleanup
                virtual ~InternalNode() noexcept;

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________
                virtual OutputStream & viz(OutputStream &) const;

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________

                //! push tail and set sire \return *this
                InternalNode & operator<<(Node * const);

                //! push all list's nodes \return *this
                InternalNode & steal(NodeList &) noexcept;


            private:
                friend class Node;
                Y_Disable_Copy_And_Assign(InternalNode); //!< discarding
                virtual void restore(Lexer &) noexcept;

            };
        }

    }

}

#endif

