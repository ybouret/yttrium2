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
            //! base class for comments
            class Comment : public Scanner
            {
            protected:

                //! setup
                /**
                 \param sid associated scanner name
                 \param com design
                 \param eof policy: accept for single line, reject for multi lines
                 */
                template <typename SID> inline
                explicit Comment(const SID    &  sid,
                                 const Design &  com,
                                 const EOFPolicy eof) :
                Scanner(sid,com,eof)
                {
                }

            public:
                virtual ~Comment() noexcept; //!< cleanup

            private:
                Y_Disable_Copy_And_Assign(Comment); //!< discarding
            protected:
                void finalize(); //!< drop dot
            };

        }

    }

}
#endif

