//! \file

#ifndef Y_Jive_Lexical_Comment_Included
#define Y_Jive_Lexical_Comment_Included 1

#include "y/jive/lexical/extension.hpp"

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
            //! base class for comments
            //
            //
            //__________________________________________________________________
            class Comment : public Extension
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
                 \param sid associated scanner name
                 \param cxp call expression
                 \param com design
                 \param eof policy: accept for single line, reject for multi lines
                 */
                template <typename SID, typename CXP> inline
                explicit Comment(const uint32_t  uid,
                                 const SID    &  sid,
                                 const CXP    &  cxp,
                                 const Design &  com,
                                 const EOFPolicy eof) :
                Extension(uid,sid,cxp,com,eof)
                {
                }


            public:
                virtual ~Comment() noexcept; //!< cleanup



            private:
                Y_Disable_Copy_And_Assign(Comment); //!< discarding
                virtual void onCall(Token &);
                virtual void onBack(Token &);
                virtual void onSent(Token &);

            protected:
                void finalize(); //!< drop "[:dot:]"
            };

        }

    }

}
#endif

