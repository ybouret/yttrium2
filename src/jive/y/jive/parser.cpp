
#include "y/jive/parser.hpp"
#include "y/ascii/printable.hpp"
#include "y/exception.hpp"

namespace Yttrium
{
    namespace Jive
    {

        Parser:: ~Parser() noexcept {}


        const Syntax::Rule & Parser:: link(const Lexical::Rule &lr, const Syntax::Activity activity)
        {
            try { return terminal(lr.name,activity,lr.motif->univocal()); }
            catch(...) { emergencyTrim(); throw; }
        }

        const Syntax::Rule & Parser:: link(const Tag &tag)
        {
            return terminal(tag,Syntax::Regular,false);
        }


        const Syntax::Rule & Parser:: operator[](const char c)
        {
            if(const Rule *rule=queryRule(c))
            {
                if(!rule->isTerminal()) throw Specific::Exception(lang->c_str(),"rule '%s' is not a Terminal",ASCII::Printable::Text(c));
                return *rule;
            }
            return mark(c);
        }

        const Syntax::Rule & Parser:: extra(const char sep, const Rule &rule)
        {
            Parser &self = *this;
            return zom( cat(self[sep], rule) );
        }

        const Syntax::Rule & Parser:: bonus(const char sep, const Rule &rule)
        {
            Parser &self = *this;
            return opt( cat(self[sep], rule) );
        }



        const Syntax::Rule & Parser:: parens(const Rule &rule)
        {
            Parser &self = *this;
            return cat( self['('], rule, self[')'] );
        }


        Syntax::Node * Parser:: parse(Source &source)
        {
            Grammar &G = *this;
            free();
            return G.run(*this,source);
        }


        const Syntax::Rule & Parser:: populate( Agg &a, const char enter, const char leave)
        {
            return a << enter << leave;
        }

        const Syntax::Rule & Parser:: populate( Agg &a, const char enter, const Rule &rule, const char separator, const char leave)
        {
            return a << enter << rule << extra(separator,rule) << leave;
        }


    }

}
