

#ifndef Y_Jive_Lexical_Plugin_Included
#define Y_Jive_Lexical_Plugin_Included 1

#include "y/jive/lexical/extension.hpp"

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
            class Plugin : public Extension
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
                Extension(uid,sid,cxp,lxr,RejectEOF),
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
            protected:
                Lexer &   root; //!< root lexer
                Token     data; //!< where to put data


            private:
                Y_Disable_Copy_And_Assign(Plugin); //!< discarding
                virtual void onCall(const Token &); //!< initialize data
                virtual void onBack(const Token &); //!< finalize data and yield lexeme
            };

#define Y_Jive_Plugin_Decl(PLUGIN)      \
/**/ typedef TypeToType<PLUGIN> Class_; \
/**/ static const Class_        Class

#define Y_Jive_Plugin_Impl(PLUGIN) \
/**/ PLUGIN:: ~PLUGIN() noexcept {} \
/**/ const PLUGIN::Class_  PLUGIN::Class = {}
            
        }

    }

}
#endif
