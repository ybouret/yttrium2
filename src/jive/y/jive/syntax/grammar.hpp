
//! \file


#ifndef Y_Jive_Syntax_Grammar_Included
#define Y_Jive_Syntax_Grammar_Included 1

#include "y/jive/syntax/rule/terminal.hpp"
#include "y/jive/syntax/rule/logical/aggegate.hpp"
#include "y/jive/syntax/rule/logical/alternate.hpp"
#include "y/jive/syntax/rule/wildcard/optional.hpp"
#include "y/jive/syntax/rule/wildcard/at-least.hpp"


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
            class Grammar : public Vizible, public Ingress< const Core::ListOf<Rule> >
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                typedef Syntax::Rule Rule; //!< alias

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup \param gid grammar name
                template <typename GID> inline
                explicit Grammar(const GID &gid) :
                name(gid), rules()
                {
                }

                virtual ~Grammar() noexcept; //!< cleanup

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________
                const Rule * query(const String &) const noexcept; //!< \return rule by name
                const Rule * query(const Tag &)    const noexcept; //!< \return rule by name
                const Rule * query(const char * const)      const; //!< \return rule by name


                //______________________________________________________________
                //
                //
                // Construction
                //
                //______________________________________________________________

                const Rule & top()       const noexcept; //!< \return top rule
                void         top(const Rule &) noexcept; //!< set top rule


                //! declare a terminal
                /**
                 \param id terminal id
                 \return created terminal
                 */
                template <typename ID>
                const Terminal & terminal(const ID &id)
                {
                    return add( new Terminal(id) );
                }

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                const Tag name; //!< grammar name

            private:
                Y_Disable_Copy_And_Assign(Grammar); //!< discarding
                Y_Ingress_Decl();                   //!< ingress
                CxxListOf<Rule> rules;              //!< grammar rules
                void append(Rule * const);          //!< append new rule

                //! append derived rule \param rule derived rule pointer \return derived rule reference
                template <typename RULE> inline
                RULE & add(RULE * const rule) {
                    append(rule); assert(this == rule->gptr);
                    return *rule;
                }
            };

        }
    }
}

#endif
