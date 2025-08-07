

#ifndef Y_Jive_Lexical_Plugin_Included
#define Y_Jive_Lexical_Plugin_Included 1

#include "y/jive/lexical/scanner.hpp"

namespace Yttrium
{
    namespace Jive
    {

        class Lexer;

        namespace Lexical
        {
            //__________________________________________________________________
            //
            //
            //
            //! base class for plugins
            //
            //
            //__________________________________________________________________
            class Plugin : public Scanner
            {
            protected:

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup
                /**
                 \param uid associated scanner uuid
                 \param sid associated scanner name
                 \param cxp call expression
                 \param com design
                 \param lxr root lexer
                 */
                template <typename SID, typename CXP> inline
                explicit Plugin(const uint32_t  uid,
                                const SID    &  sid,
                                const CXP    &  cxp,
                                Lexer &         lxr) :
                Scanner(uid,sid,lxr,RejectEOF),
                join(cxp),
                root(lxr),
                data()
                {
                }


            public:
                virtual ~Plugin() noexcept; //!< cleanup

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                const Tag join; //!< call expression
            protected:
                Lexer &   root; //!< root lexer
                Token     data; //!< where to put data

                void      yield(); //!< transform collected data in to lexeme

            private:
                Y_Disable_Copy_And_Assign(Plugin); //!< discarding
                virtual void onCall(const Token &);
                virtual void onBack(const Token &);

            };

        }

    }

}
#endif
