
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

            //__________________________________________________________________
            //
            //
            //
            //! Grammar is a list of rules
            //
            //
            //__________________________________________________________________
            class Grammar : public Vizible,
            public Ingress< const Core::ListOf<Rule> >
            {
            public:
                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup \param gid grammar name
                template <typename GID> inline
                explicit Grammar(const GID &gid) :
                name(gid)
                {
                }

                virtual ~Grammar() noexcept; //!< cleanup

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________
                const Rule * query(const String &) const noexcept;
                const Rule * query(const Tag &)    const noexcept;
                const Rule * query(const char * const)      const;

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                const Tag name;

            private:
                Y_Disable_Copy_And_Assign(Grammar); //!< discarding
                Y_Ingress_Decl();                   //!< ingress
                CxxListOf<Rule> rules;              //!< grammar rules
                void append(Rule * const);          //!< append new rule
            };

        }
    }
}

#endif
