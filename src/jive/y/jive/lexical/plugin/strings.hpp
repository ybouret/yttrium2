#ifndef Y_Jive_Lexical_Strings_Included
#define Y_Jive_Lexical_Strings_Included 1

#include "y/jive/lexical/plugin.hpp"

namespace Yttrium
{
    namespace Jive
    {

        namespace Lexical
        {
            class Strings : public Plugin
            {
            protected:
                //! setup
                /**
                 \param uid associated scanner uuid
                 \param sid associated scanner name
                 \param cxp call expression
                 \param com design
                 \param lxr root lexer
                 */
                template <typename SID,typename CXP> inline
                explicit Strings(const uint32_t  uid,
                                 const SID    &  sid,
                                 const CXP    &  cxp,
                                 Lexer &         lxr) :
                Plugin(uid,sid,cxp,lxr)
                {
                    back(cxp,Regular);
                }

            public:
                //! cleanup
                virtual ~Strings() noexcept;

            protected:
                void initialize();

            private:
                Y_Disable_Copy_And_Assign(Strings);
                virtual void onSent(Token &);

            };
        }

    }

}

#endif

