
//! \file


#ifndef Y_Jive_Syntax_Grammar_Included
#define Y_Jive_Syntax_Grammar_Included 1

#include "y/jive/syntax/rule.hpp"

namespace Yttrium
{
    namespace Jive
    {

        namespace Syntax
        {

            class Grammar : public Vizible,
            public Ingress< const Core::ListOf<Rule> >
            {
            public:
                template <typename GID> inline
                explicit Grammar(const GID &gid) :
                name(gid)
                {
                }

                virtual ~Grammar() noexcept;


                const Tag name;

            private:
                Y_Disable_Copy_And_Assign(Grammar);
                Y_Ingress_Decl();
                CxxListOf<Rule> rules;
            };

        }
    }
}

#endif
