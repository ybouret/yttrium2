


#ifndef Y_Jive_Lexical_BString_Included
#define Y_Jive_Lexical_BString_Included 1

#include "y/jive/lexical/plugin/strings.hpp"

namespace Yttrium
{
    namespace Jive
    {

        namespace Lexical
        {

            class BString : public Strings
            {
            public:
                static const uint32_t       UUID = Y_FOURCC('B','S','T','R');
                static const char           JOIN = '<';
                static const char           QUIT = '>';
                Y_Jive_Plugin_Decl(BString);

                //! setup
                /**
                 \param uid associated scanner uuid
                 \param sid associated scanner name
                 \param cxp call expression
                 \param com design
                 \param lxr root lexer
                 */
                template <typename SID> inline
                explicit BString(const SID    &  sid,
                                 Lexer &         lxr) :
                Strings(UUID,sid,JOIN,QUIT,lxr)
                {
                    initialize();
                    finalize();
                }

                //! cleanup
                virtual ~BString() noexcept;

            private:
                Y_Disable_Copy_And_Assign(BString);
                void finalize();
            };
        }

    }

}

#endif

