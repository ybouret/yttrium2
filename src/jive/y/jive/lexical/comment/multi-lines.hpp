

//! \file

#ifndef Y_Jive_Lexical_MultiLinesComment_Included
#define Y_Jive_Lexical_MultiLinesComment_Included 1

#include "y/jive/lexical/comment.hpp"

namespace Yttrium
{
    namespace Jive
    {

        namespace Lexical
        {

            class MultiLinesComment : public Comment
            {
            public:
                template <typename SID, typename RXP> inline
                explicit MultiLinesComment(const SID    &sid,
                                           const RXP    &rxp,
                                           const Design &com) :
                Comment(sid,com,RejectEOF)
                {
                    back(rxp,Regular);
                    setup();
                }


                virtual ~MultiLinesComment() noexcept;

            private:
                Y_Disable_Copy_And_Assign(MultiLinesComment);
                void setup();

            };
        }

    }

}

#endif

