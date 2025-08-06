
//! \file

#ifndef Y_Jive_Lexical_Scanner_Included
#define Y_Jive_Lexical_Scanner_Included 1

#include "y/jive/lexical/rule.hpp"
#include "y/jive/lexical/unit.hpp"
#include "y/jive/regexp.hpp"

#include "y/pointer/keyed.hpp"
#include "y/pointer/arc.hpp"

namespace Yttrium
{
    namespace Jive
    {

        namespace Lexical
        {

            enum Status
            {
                FoundEOF,
                EmitUnit,
                CtrlCall,
                CtrlBack
            };

            class Scanner : public CountedObject
            {
            public:
                typedef Keyed< String,ArcPtr<Scanner> > Pointer;

                
                template <typename SID> inline
                explicit Scanner(const SID &sid, const Dictionary::Pointer &pdb) :
                CountedObject(),
                name(sid),
                code( Impl(name) ),
                hDict(pdb),
                noData("")
                {
                }

                virtual ~Scanner() noexcept;

                const String & key() const noexcept;

                template <typename RID, typename RXP>
                void decl(const RID &              rid,
                          const RXP &              rxp,
                          const Attribute          attr,
                          const bool               emit)
                {
                    const Tag    rname = rid;
                    const Motif  motif = RegExp::Compile(rxp, & *hDict);
                    add( new Rule(rname,motif,attr,emit,noData) );
                }

                Unit * operator()(Source &);

                Status operator()(Source &, void **hook);
                


                const Tag name;
            private:
                class Code;
                Code * const code;

                Y_Disable_Copy_And_Assign(Scanner);
                static Code *Impl(const Tag &);
                void add(Rule * const rule);

            public:
                const Dictionary::Pointer hDict;
                const Tag                 noData;
            };


        }
    }

}

#endif

