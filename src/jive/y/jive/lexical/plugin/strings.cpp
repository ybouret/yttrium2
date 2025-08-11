#include "y/jive/lexical/plugin/strings.hpp"
#include "y/format/hexadecimal.hpp"

namespace Yttrium
{
    namespace Jive
    {

        namespace Lexical
        {
            Strings:: ~Strings() noexcept {}

            void Strings:: initialize()
            {
                send("core","[:core:]");
                send("hexa","\\\\x[:xdigit:][:xdigit:]");
                send("esc","\\\\[nrtfv\\x22\\x27<>\\\\]");
                halt("unexpected","\\\\.?");
            }

            namespace
            {
                static inline void EscapeChar(uint8_t &code)
                {
                    switch(code)
                    {

                        case 'n': code='\n'; break;
                        case 'r': code='\r'; break;
                        case 't': code='\t'; break;
                        case 'v': code='\v'; break;
                        case 'f': code='\f'; break;

                            // direct
                        default:
                            break;
                    }
                }
            }

            static inline void EscapeHexa(Token &token)
            {
                assert('\\' == **token.head);
                assert('x'  == **token.head->next);
                const unsigned hi = Hexadecimal::ToDec( **token.skip().skip().head );
                const unsigned lo = Hexadecimal::ToDec( **token.skip().head );

                **token.head = uint8_t( hi << 4 | lo );

            }

            void Strings:: onSent(Token &token)
            {

                switch(token.size)
                {
                    case 2:
                        assert('\\' == **token.head);
                        EscapeChar(**token.skip().head);
                        break;

                    case 4:
                        EscapeHexa(token);
                        break;

                    default:
                        break;
                }
                data.mergeTail(token);
            }


            size_t Strings:: serialize(OutputStream &fp) const
            {
                return emitUUID(fp);
            }
        }
    }

}
