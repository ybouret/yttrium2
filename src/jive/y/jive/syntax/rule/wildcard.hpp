

//! \file

#ifndef Y_Jive_Syntax_Wildcard_Included
#define Y_Jive_Syntax_Wildcard_Included 1

#include "y/jive/syntax/rule/internal.hpp"

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
            //! Wildcard inner rule
            //
            //
            //__________________________________________________________________
            class Wildcard : public Internal
            {
            protected:
                //! setup \param r rule name  \param u rule uuid \param f foreign rule
                template <typename RID> inline
                explicit Wildcard(const RID     &r,
                                  const uint32_t u,
                                  const Rule &   f) :
                Internal(r,u),
                rule(f)
                {
                }

            public:
                virtual ~Wildcard() noexcept; //!< cleanup

                virtual OutputStream & vizPost(OutputStream &) const;

                const Rule &rule; //!< foreign persistent rule
            private:
                Y_Disable_Copy_And_Assign(Wildcard); //!< discarding
            };


        }

    }

}

#endif

