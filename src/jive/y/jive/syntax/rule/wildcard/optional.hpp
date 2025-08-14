

//! \file

#ifndef Y_Jive_Syntax_Optional_Included
#define Y_Jive_Syntax_Optional_Included 1

#include "y/jive/syntax/rule/wildcard.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Syntax
        {

            //__________________________________________________________________
            //
            //
            //
            //! Optional rule
            //
            //
            //__________________________________________________________________
            class Optional : public Wildcard
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                static const uint32_t UUID = Y_FOURCC('O', 'P', 'T', '_'); //!< alias

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup \param rid rule name \param f foreign rule
                template <typename RID> inline
                explicit Optional(const RID &rid, const Rule &f) :
                Wildcard(rid,UUID,f)
                {
                }

                //! cleanup
                virtual ~Optional() noexcept;

                //______________________________________________________________
                //
                //
                // Interface
                //
                //______________________________________________________________
                virtual bool           accepts(Y_Jive_XRule_Args) const;
                virtual OutputStream & vizDecl(OutputStream &)    const;


            private:
                Y_Disable_Copy_And_Assign(Optional); //!< discarding
            };
        }

    }

}

#endif

