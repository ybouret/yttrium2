
//! \file

#ifndef Y_Jive_Lexical_SingleLineComment_Included
#define Y_Jive_Lexical_SingleLineComment_Included 1

#include "y/jive/lexical/comment.hpp"

namespace Yttrium
{
    namespace Jive
    {

        namespace Lexical
        {

            class SingleLineComment : public Comment
            {
            public:
                template <typename SID> inline
                explicit SingleLineComment(const SID    &sid,
                                           const Design &com) :
                Comment(sid,com,AcceptEOF)
                {
                    setup();
                }


                virtual ~SingleLineComment() noexcept;
                
            private:
                Y_Disable_Copy_And_Assign(SingleLineComment);
                void setup();

            };
        }

    }

}

#endif

