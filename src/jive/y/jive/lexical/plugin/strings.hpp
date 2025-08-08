#ifndef Y_Jive_Lexical_Strings_Included
#define Y_Jive_Lexical_Strings_Included 1

#include "y/jive/lexical/plugin.hpp"

namespace Yttrium
{
    namespace Jive
    {

        namespace Lexical
        {
            //__________________________________________________________________
            //
            //
            //
            //! Common class for strinfs
            //
            //
            //__________________________________________________________________
            class Strings : public Plugin
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
                 \param cxp back expression
                 \param bxp back expression
                 \param lxr root lexer
                 */
                template <typename SID,typename CXP, typename BXP> inline
                explicit Strings(const uint32_t  uid,
                                 const SID    &  sid,
                                 const CXP    &  cxp,
                                 const BXP    &  bxp,
                                 Lexer &         lxr) :
                Plugin(uid,sid,cxp,lxr)
                {
                    back(bxp,Regular);
                }

            public:
                //! cleanup
                virtual ~Strings() noexcept;

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________
            protected:
                void initialize(); //!< register all content to send to data

            private:
                Y_Disable_Copy_And_Assign(Strings); //!< discarding
                virtual void onSent(Token &);       //!< process sent token

            };
        }

    }

}

#endif

