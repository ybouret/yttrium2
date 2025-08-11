
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
            class InternalNode : public Node, public NodeList
            {
            public:
                virtual ~InternalNode() noexcept;

                //! push tail and set sire
                InternalNode & operator<<(Node * const);


            private:
                friend class Node;
                Y_Disable_Copy_And_Assign(InternalNode);
                
                explicit InternalNode(const Internal &) noexcept;
                virtual void restore(Lexer &) noexcept;

            };
        }

    }

}

#endif

