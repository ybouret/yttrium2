
#ifndef Y_Jive_Lexical_JString_Included
#define Y_Jive_Lexical_JString_Included 1

#include "y/jive/lexical/plugin/strings.hpp"

namespace Yttrium
{
    namespace Jive
    {

        namespace Lexical
        {

            class JString : public Strings
            {
            public:
                static const uint32_t       UUID = Y_FOURCC('J','S','T','R');
                static const char           JOIN = '"';
                Y_Jive_Plugin_Decl(JString);

                //! setup
                /**
                 \param uid associated scanner uuid
                 \param sid associated scanner name
                 \param cxp call expression
                 \param com design
                 \param lxr root lexer
                 */
                template <typename SID> inline
                explicit JString(const SID    &  sid,
                                 Lexer &         lxr) :
                Strings(UUID,sid,JOIN,JOIN,lxr)
                {
                    initialize();
                    finalize();
                }

                //! cleanup
                virtual ~JString() noexcept;

            private:
                Y_Disable_Copy_And_Assign(JString);
                void finalize();
            };
        }

    }

}

#endif

