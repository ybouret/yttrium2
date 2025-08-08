

#ifndef Y_Jive_Lexical_RString_Included
#define Y_Jive_Lexical_RString_Included 1

#include "y/jive/lexical/plugin/strings.hpp"

namespace Yttrium
{
    namespace Jive
    {

        namespace Lexical
        {

            class RString : public Strings
            {
            public:
                static const uint32_t       UUID = Y_FOURCC('R','S','T','R');
                static const char           JOIN = '\'';
                Y_Jive_Plugin_Decl(RString);

                //! setup
                /**
                 \param uid associated scanner uuid
                 \param sid associated scanner name
                 \param cxp call expression
                 \param com design
                 \param lxr root lexer
                 */
                template <typename SID> inline
                explicit RString(const SID    &  sid,
                                 Lexer &         lxr) :
                Strings(UUID,sid,JOIN,lxr)
                {
                    initialize();
                    finalize();
                }

                //! cleanup
                virtual ~RString() noexcept;

            private:
                Y_Disable_Copy_And_Assign(RString);
                void finalize();
            };
        }

    }

}

#endif

