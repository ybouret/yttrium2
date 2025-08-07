
//! \file

#ifndef Y_Jive_Lexical_Extension_Included
#define Y_Jive_Lexical_Extension_Included 1

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
            //! base class for extension
            //
            //
            //__________________________________________________________________
            class Extension : public Scanner
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
                explicit Extension(const uint32_t  uid,
                                   const SID    &  sid,
                                   const CXP    &  cxp,
                                   const Design &  com,
                                   const EOFPolicy eof) :
                Scanner(uid,sid,com,eof),
                join(cxp)
                {
                }


            public:
                virtual ~Extension() noexcept; //!< cleanup

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                const Tag join; //!< call expression

            private:
                Y_Disable_Copy_And_Assign(Extension);
            };
        }

    }

}

#endif

