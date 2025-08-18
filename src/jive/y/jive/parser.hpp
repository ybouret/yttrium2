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

            //! setup \param id name and lang
            template <typename ID> inline
            explicit Parser(const ID &id) :
            Lexer(id), Syntax::Grammar(name,this)
            {
            }

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
             \return compile Terminal as Rule
             */
            template <typename RXP>
            const Rule & mark(const RXP &rxp) {
                return link(emit(rxp),Syntax::Divider);
            }





            //! cleanup
            virtual ~Parser() noexcept;

        private:
            Y_Disable_Copy_And_Assign(Parser); //!< discarding

            //! \return syntax rule for lexical rule
            const Rule & link(const Lexical::Rule &, const Syntax::Activity);

        };
    }

}

#endif

