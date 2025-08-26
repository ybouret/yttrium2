
#include "y/chemical/weasel/parser.hpp"
#include "y/chemical/formula.hpp"
#include "y/chemical/equilibrium.hpp"
#include "y/jive/lexical/plugin/rstring.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        Weasel:: Parser:: ~Parser() noexcept {}


        Weasel:: Parser:: Parser() : Jive::Parser(CallSign)
        {
            Agg &WEASEL = agg(lang);

            Alt &STATEMENT = alt("STATEMENT");
            WEASEL << zom(STATEMENT);

            //------------------------------------------------------------------
            //
            // Whitespaces and empty statement
            //
            //------------------------------------------------------------------
            const Rule &WHITE     = alt("WHITE") << markNL("ENDL","[:endl:]") << mark("BLNK", "[ \t]");
            const Rule &SEPARATOR = mark(';');
            const Rule &OPT_SEP   = opt(SEPARATOR);

            STATEMENT << SEPARATOR;                // single separator
            STATEMENT << cat(oom(WHITE),OPT_SEP);  // remaining blank line

            //------------------------------------------------------------------
            //
            // Common rules for Equilibria/Formula
            //
            //------------------------------------------------------------------
            const Rule &COEF      = term(Coef,"[:digit:]+");
            const Rule &OPT_COEF  = opt(COEF);
            Agg        &FORMULA   = agg(Formula::CallSign);
            const Rule &PLUS      = term('+');
            const Rule &MINUS     = term('-');
            const Rule &SIGN      = pick(PLUS,MINUS);
            //const Rule &STRING    = plugin(Jive::Lexical::RString::Class,StringID);


            //------------------------------------------------------------------
            //
            // Create Formula
            //
            //------------------------------------------------------------------
            {
                const Rule &NAME = term(Formula::Name,"[:upper:][[:lower:]_]*");
                Agg        &MULT = act(Formula::Mult);
                const Rule &BODY = act(Formula::Body) << MULT << zom(MULT);
                Alt        &ITEM = alt("Item");
                MULT    << ITEM     << OPT_COEF;
                ITEM    << NAME     << parens(BODY);
                FORMULA << BODY << opt(agg(Formula::Z) << '^' << OPT_COEF << SIGN);
            }
            STATEMENT << FORMULA;

            //------------------------------------------------------------------
            //
            // Create Equilibrium
            //
            //------------------------------------------------------------------
            const Rule &SPACE     = zom(WHITE);

            {
                Agg & EQUILIBRIUM = agg(Equilibrium::CallSign);

                // prolog
                EQUILIBRIUM << term("EID","@[:word:]+") << SPACE << ':';

                // content
                const Rule & ACTOR      = ( agg("Actor") << OPT_COEF << SPACE << FORMULA );
                const Rule & XACTOR     = ( grp("XActor") << SPACE << '+' << SPACE << ACTOR);
                const Rule & ACTORS     = ( grp("Actors") << ACTOR << zom(XACTOR) );
                const Rule & OPT_ACTORS = opt(ACTORS);
                const Rule & PROD       = ( agg(Equilibrium::Prod) << OPT_ACTORS);
                const Rule & REAC       = ( agg(Equilibrium::Reac) << OPT_ACTORS);

                EQUILIBRIUM << SPACE << PROD << SPACE << mark(Equilibrium::Arrows) << SPACE << REAC << SPACE << ':';

                // constant


                STATEMENT << EQUILIBRIUM;
            }




            render();
        }

    }

}


