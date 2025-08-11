
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

            //__________________________________________________________________
            //
            //
            //
            //! Single Line Comment
            //
            //
            //__________________________________________________________________
            class SingleLineComment : public Comment
            {
            public:
                static const uint32_t UUID = Y_FOURCC('C', 'O', 'M','1'); //!< alias

                static Scanner * Load(InputStream  &,
                                      Lexer        &,
                                      TagDB        &);

                //! construct
                /**
                 \param sid comment name
                 \param cxp call expression
                 \param com design
                 */
                template <typename SID, typename CXP> inline
                explicit SingleLineComment(const SID    &sid,
                                           const CXP    &cxp,
                                           const Design &com) :
                Comment(UUID,sid,cxp,com,AcceptEOF)
                {
                    setup();
                }

                //! cleanup
                virtual ~SingleLineComment() noexcept;

                virtual size_t serialize(OutputStream&) const;


            private:
                Y_Disable_Copy_And_Assign(SingleLineComment); //!< discarding
                void setup(); //!< return on newline, drop otherwise

            };
        }

    }

}

#endif

