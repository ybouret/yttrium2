

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
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                static const uint32_t UUID = Y_FOURCC('C', 'O', 'M','2');  //!< alias
                static Scanner *      Load(InputStream &,Lexer &,TagDB &); //!< loaded \return multi lines comment

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! construct
                /**
                 \param sid comment name
                 \param cxp call expression
                 \param bxp back expression, assuming not endl
                 \param com design
                 */
                template <typename SID, typename CXP, typename RXP> inline
                explicit MultiLinesComment(const SID    &sid,
                                           const CXP    &cxp,
                                           const RXP    &bxp,
                                           const Design &com) :
                Comment(UUID,sid,cxp,com,RejectEOF),
                quit(bxp)
                {
                    back(*quit,Regular);
                    setup();
                }

                //! cleanup
                virtual ~MultiLinesComment() noexcept;

                //______________________________________________________________
                //
                //
                // Interface
                //
                //______________________________________________________________
                virtual size_t serialize(OutputStream &fp) const;

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                const Tag quit; //!< back expression, saved
                
            private:
                Y_Disable_Copy_And_Assign(MultiLinesComment); //!< discarding
                void setup(); //!< drop endl, drop dot

            };
        }

    }

}

#endif

