
//! \file


#ifndef Y_Jive_Syntax_Grammar_Included
#define Y_Jive_Syntax_Grammar_Included 1

#include "y/jive/syntax/rule/terminal.hpp"
#include "y/jive/syntax/rule/logical/aggegate.hpp"
#include "y/jive/syntax/rule/logical/alternate.hpp"



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
                typedef Syntax::Rule      Rule;         //!< alias
                typedef Syntax::Aggregate Agg;          //!< alias
                typedef Syntax::Alternate Alt;          //!< alias
                typedef Syntax::Logical   Logical;      //!< alias
                static const char         AltSep = '|'; //!< alias
                static const char         AggSep = ' '; //!< alias

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup \param gid grammar name \param ptr optional parser address
                template <typename GID> inline
                explicit Grammar(const GID &gid, Parser * const ptr) :
                lang(gid),
                rules(),
                pptr(ptr)
                {
                }

                virtual ~Grammar() noexcept; //!< cleanup

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________
                Node *run(Lexer &, Source &);
                void  top(const Rule &) noexcept; //!< set top-level rupe

                OutputStream & viz(OutputStream &) const; //!< emit GraphViz \return stream

                //______________________________________________________________
                //
                //
                // Construction
                //
                //______________________________________________________________
                const Rule * queryRule(const String &) const noexcept; //!< \return rule by name
                const Rule * queryRule(const Tag &)    const noexcept; //!< \return rule by name
                const Rule * queryRule(const char * const)      const; //!< \return rule by name
                const Rule * queryRule(const char)              const; //!< \return rule by name

                


                //! declare a terminal
                /**
                 \param id       terminal id
                 \param activity activity of terminal
                 \param univocal univocal associated pattern
                 \return created terminal
                 */
                template <typename ID>
                const Terminal & terminal(const ID   &   id,
                                          const Activity activity = Regular,
                                          const bool     univocal = false)
                {
                    return add( new Terminal(id,activity,univocal) );
                }

                //! create a new Normal aggregate
                /**
                 \param id rule name
                 \return a new empty aggregate
                 */
                template <typename ID>
                Aggregate & agg(const ID &id)
                {
                    return add( new AggregateIs<Normal>(id) );
                }

                //! create a new Acting aggregate
                /**
                 \param id rule name
                 \return a new empty aggregate
                 */
                template <typename ID>
                Aggregate & act(const ID &id)
                {
                    return add( new AggregateIs<Acting>(id) );
                }

                //! create a new Grouping aggregate
                /**
                 \param id rule name
                 \return a new empty aggregate
                 */
                template <typename ID>
                Aggregate & grp(const ID &id)
                {
                    return add( new AggregateIs<Grouping>(id) );
                }


                //! create a new alternate
                /**
                 \param id rule name
                 \return a new empty alternate
                 */
                template <typename ID>
                Alternate & alt(const ID &id)
                {
                    return add( new Alternate(id) );
                }


                const Rule & opt(const Rule &); //!< \return new optional   from existing rule
                const Rule & oom(const Rule &); //!< \return new OneOrMore  from existing rule
                const Rule & zom(const Rule &); //!< \return new ZeroOrMore from existing rule

                const Rule & cat(const Rule &, const Rule &);               //!< \return aggregate
                const Rule & cat(const Rule &, const Rule &, const Rule &); //!< \return aggregate

                const Rule & pick(const Rule &, const Rule &);               //!< \return alternate
                const Rule & pick(const Rule &, const Rule &, const Rule &); //!< \return alternate


                static Node * AST(Node * const) noexcept;


                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                const Tag       lang;  //!< grammar language
            private:                   //|
                CxxListOf<Rule> rules; //!< grammar rules
            public:                    //|
                Parser * const  pptr;  //!< Parser pointer if any

            private:
                Y_Disable_Copy_And_Assign(Grammar); //!< discarding
                Y_Ingress_Decl();                   //!< ingress
                void append(Rule * const);          //!< append new rule

                //! append derived rule \param rule derived rule pointer \return derived rule reference
                template <typename RULE> inline
                RULE & add(RULE * const rule) {
                    append(rule); assert(pptr == rule->pptr);
                    return *rule;
                }

                Node *        onSuccess(Node *, Lexer & , Source & );
                Node *        onFailure(Lexer &, Source &);


                static String PreFormat(const Rule &);                       //!< \return pre formatted name
                String        buildName(const Manifest &, const char) const; //!< \return manifest name
                void          sendTo(Exception &, const Lexeme &) const;     //!< append description to exception


                //! \param manifest manifest \param sep separator \return named LOGICAL with manifest
                template <typename LOGICAL> inline
                LOGICAL & create(Manifest &manifest, const char sep)
                {
                    const String    rid  = buildName(manifest,sep);
                    LOGICAL * const rule = new LOGICAL(rid);
                    (**rule).swapListFor(*manifest);
                    return add(rule);
                }
            };

        }
    }
}

#endif
