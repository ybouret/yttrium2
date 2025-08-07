

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

            //__________________________________________________________________
            //
            //
            //
            //! Multi Lines Comment
            //
            //
            //__________________________________________________________________
            class MultiLinesComment : public Comment
            {
            public:
                //! construct
                /**
                 \param sid comment name
                 \param rxp returning expression, assuming not endl
                 \param com design
                 */
                template <typename SID, typename RXP> inline
                explicit MultiLinesComment(const SID    &sid,
                                           const RXP    &rxp,
                                           const Design &com) :
                Comment(sid,com,RejectEOF)
                {
                    back(rxp,Regular);
                    setup();
                }

                //! cleanup
                virtual ~MultiLinesComment() noexcept;

            private:
                Y_Disable_Copy_And_Assign(MultiLinesComment); //!< discarding
                void setup(); //!< drop endl, drop dot

            };
        }

    }

}

#endif

