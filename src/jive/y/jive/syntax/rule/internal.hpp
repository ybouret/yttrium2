

//! \file

#ifndef Y_Jive_Syntax_InternalRule_Included
#define Y_Jive_Syntax_InternalRule_Included 1

#include "y/jive/syntax/rule.hpp"

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
            //! Internal rule base class
            //
            //
            //__________________________________________________________________
            class Internal : public Rule
            {
                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
            protected:

                //! setup \param r rule name \param u rule uuid
                template <typename RID> inline
                explicit Internal(const RID     &r,
                                  const uint32_t u) :
                Rule(r,IsInternal,u)
                {
                }

            public:
                //! cleanup
                virtual ~Internal() noexcept;

            private:
                Y_Disable_Copy_And_Assign(Internal); //!< discarding
            };


        }
    }

}

#endif

