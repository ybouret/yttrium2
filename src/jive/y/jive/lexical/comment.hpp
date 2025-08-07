//! \file

#ifndef Y_Jive_Lexical_Comment_Included
#define Y_Jive_Lexical_Comment_Included 1

#include "y/jive/lexical/scanner.hpp"

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
            class Comment : public Scanner
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
                explicit Comment(const SID    &  sid,
                                 const CXP    &  cxp,
                                 const Design &  com,
                                 const EOFPolicy eof) :
                Scanner(sid,com,eof),
                join(cxp)
                {
                }


            public:
                virtual ~Comment() noexcept; //!< cleanup

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                const Tag join; //!< call expression

            private:
                Y_Disable_Copy_And_Assign(Comment); //!< discarding
                virtual void onCall(const Token &);
                virtual void onBack(const Token &);

            protected:
                void finalize(); //!< drop "[:dot:]"
            };

        }

    }

}
#endif

