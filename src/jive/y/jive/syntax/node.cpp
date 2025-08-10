
#include "y/jive/syntax/node.hpp"
#include "y/type/destruct.hpp"

namespace Yttrium
{
    namespace Jive
    {

        namespace Syntax
        {
            Node:: ~Node() noexcept
            {
                assert(0!=data);
                switch(type)
                {
                    case IsTerminal: { Lexeme * const lx = queryLexeme(); if(lx) delete lx; } break;
                    case IsInternal:  Destruct(static_cast<XList *>(data)); break;
                }
                Y_Memory_BZero(wksp);
            }

            Node * Node:: Make(Lexeme * const lx)
            {
                try { return new Node(lx);     }
                catch(...) { delete lx; throw; }
            }

            Node:: Node(Lexeme * const lx) noexcept :
            type(IsTerminal),
            sire(0),
            data(0),
            wksp(),
            next(0),
            prev(0)
            {
                Coerce(data) = Y_Memory_BZero(wksp);
                *(Lexeme **) data = lx;
            }

            Node:: Node() noexcept :
            type(IsInternal),
            sire(0),
            data(0),
            wksp(),
            next(0),
            prev(0)
            {
                new ( Coerce(data) = Y_Memory_BZero(wksp) ) XList();
            }

            Node * Node:: Make()
            {
                return new Node();
            }

            Lexeme * Node:: queryLexeme() const noexcept
            {
                assert(IsTerminal);
                Lexeme * const lx = *(Lexeme **) data;
                return lx;
            }

            XList  & Node:: returnXList() const noexcept
            {
                assert(IsInternal);
                return *(XList *) data;
            }


            

        }

    }

}
