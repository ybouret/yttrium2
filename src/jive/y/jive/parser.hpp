//! \file


#ifndef Y_Jive_Parser_Included
#define Y_Jive_Parser_Included 1

#include "y/jive/syntax/grammar.hpp"


namespace Yttrium
{
    namespace Jive
    {

        //______________________________________________________________________
        //
        //
        //
        //! Parser = Lexer + Grammar
        //
        //
        //______________________________________________________________________
        class Parser : public Lexer, public Syntax::Grammar
        {
        public:

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning ( disable : 4355 )
#endif
            //! setup \param id name and lang
            template <typename ID> inline
            explicit Parser(const ID &id) :
            Lexer(id), Syntax::Grammar(name,this)
            {
            }
#if defined(_MSC_VER)
#pragma warning (pop)
#endif

            //! cleanup
            virtual ~Parser() noexcept;

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! \return AST from source and reset Lexer
            XNode * parse(Source &);


            //__________________________________________________________________
            //
            //
            // Low-Level Methods
            //
            //__________________________________________________________________

            //! create a new Regular terminal
            /**
             \param rid terminal name
             \param rxp terminal regular expression
             \return compiled Terminal as Rule
             */
            template <typename RID, typename RXP>
            const Rule & term(const RID &rid, const RXP &rxp) {
                return link(emit(rid,rxp),Syntax::Regular);
            }

            //! create a new Regular terminal
            /**
             \param rxp terminal regular expression and name
             \return compiled Terminal as Rule
             */
            template <typename RXP>
            const Rule & term(const RXP &rxp) {
                return link(emit(rxp,rxp),Syntax::Regular);
            }



            //! create a new Divider terminal
            /**
             \param rid terminal name
             \param rxp terminal regular expression
             \return compile Terminal as Rule
             */
            template <typename RID, typename RXP>
            const Rule & mark(const RID &rid, const RXP &rxp) {
                return link(emit(rid,rxp),Syntax::Divider);
            }

            //! create a new Divider terminal
            /**
             \param rxp terminal name and regular expression
             \return compiled Terminal as Rule
             */
            template <typename RXP>
            const Rule & mark(const RXP &rxp) {
                return link(emit(rxp),Syntax::Divider);
            }

            //! \param rid rule id \param rxp end of line \return terminal end of line
            template <typename RID, typename RXP>
            const Rule & termNL(const RID &rid, const RXP &rxp ) {
                return link(endl(rid,rxp,true),Syntax::Regular);
            }

            //! \param rid rule id \param rxp end of line \return divider end of line
            template <typename RID, typename RXP>
            const Rule & markNL(const RID &rid, const RXP &rxp ) {
                return link(endl(rid,rxp,true),Syntax::Divider);
            }

            //! \param rxp end of line expression and name \return divider end of line
            template <typename RXP>
            const Rule & markNL(const RXP &rxp) {
                return markNL(rxp,rxp);
            }



            const Rule & operator[](const char); //!< \return marker on the fly

            //! create a terminal from a plugin
            /**
             \param clid class identifier
             \param sid  plugin name
             \return compiled Terminal as Rule
             */
            template <typename CLASS, typename SID> inline
            const Rule & plugin(const CLASS &clid, const SID &sid)
            {
                return link( connect(clid,sid) );
            }






            //__________________________________________________________________
            //
            //
            // High-Level Methods
            //
            //__________________________________________________________________

            //! helper \return zom( cat(sep,rule) )
            const Rule & extra(const char,const Rule &);

            //! helper \return opt( cat(sep,rule) )
            const Rule & bonus(const char,const Rule &);

            //! helper \return cat('(',rule,')')
            const Rule & parens(const Rule &);

            //! create an empty list syntax
            /**
             \param id list name
             \param enter enter list
             \param leave leave list
             \return id : enter leave
             */
            template <typename ID> inline
            const Rule & emptyList(const ID &id, const char enter, const char leave)
            {
                return populate(agg(id),enter,leave);
            }

            //! create an heavy list syntax
            /**
             \param id        list name
             \param enter     enter list
             \param rule      element rule
             \param separator element separator
             \param leave     leave list
             \return id : enter rule (separator rule)* leave
             */
            template <typename ID> inline
            const Rule & heavyList(const ID & id,
                                    const char enter,
                                    const Rule &rule,
                                    const char separator,
                                    const char leave)
            {
                return populate(agg(id),enter,rule,separator,leave);
            }




        private:
            Y_Disable_Copy_And_Assign(Parser); //!< discarding

            //! \return syntax rule for lexical rule
            const Rule & link(const Lexical::Rule &, const Syntax::Activity);

            //! \return terminal matching plugin
            const Rule & link(const Tag &);

            //! \return populated empty list
            const Rule & populate( Agg &, const char, const char);

            //! \return populated heavy list
            const Rule & populate( Agg &, const char, const Rule &, const char, const char);

        };
    }

}

#endif

