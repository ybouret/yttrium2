
//! \file

#ifndef Y_Jive_Lexical_Scanner_Included
#define Y_Jive_Lexical_Scanner_Included 1

#include "y/jive/lexical/rule.hpp"
#include "y/jive/lexical/unit.hpp"
#include "y/jive/lexical/design.hpp"

#include "y/jive/regexp.hpp"

#include "y/pointer/keyed.hpp"
#include "y/pointer/arc.hpp"
#include "y/pointer/auto.hpp"

namespace Yttrium
{
    namespace Jive
    {

        namespace Lexical
        {

            //__________________________________________________________________
            //
            //
            //! scanner run result
            //
            //__________________________________________________________________
            enum Status
            {
                FoundEOF, //!< found eof
                EmitUnit, //!< found unit to emit
                CtrlCall, //!< found Call control
                CtrlBack  //!< found Back control
            };

            //__________________________________________________________________
            //
            //
            //! scanner EOF policy
            //
            //__________________________________________________________________
            enum EOFPolicy
            {
                AcceptEOF, //!< ok to stop during scan
                RejectEOF  //!< error if EOF during scan
            };


            //__________________________________________________________________
            //
            //
            //
            //! Scanner to apply a set of rules
            //
            //
            //__________________________________________________________________
            class Scanner : public CountedObject
            {
            public:
                //______________________________________________________________
                //
                //
                // Defintitions
                //
                //______________________________________________________________
                typedef Keyed< String,ArcPtr<Scanner> > Pointer;


                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
                template <typename SID> inline
                explicit Scanner(const SID    &  sid,
                                 const Design &  com,
                                 const EOFPolicy eof) :
                CountedObject(),
                name(sid),
                code( Impl(name) ),
                design(com),
                policy(eof)
                {
                }

                virtual ~Scanner() noexcept;

                //______________________________________________________________
                //
                //
                // Interface
                //
                //______________________________________________________________
                virtual void onCall(const Token &enter) = 0;
                virtual void onBack(const Token &leave) = 0;

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________

                const String & key() const noexcept; //!< \return *name

                template <typename RID, typename RXP>
                void decl(const RID &              rid,
                          const RXP &              rxp,
                          const Attribute          attr,
                          const bool               emit)
                {
                    const Tag    rname = rid;
                    const Motif  motif = RegExp::Compile(rxp, & *design.pdb );
                    add( new Rule(rname,motif,attr,emit,design.nil.tag) );
                }

                template <typename SID, typename RXP>
                void call(const SID &     sid,
                          const RXP &     rxp,
                          const Attribute attr = Regular)
                {
                    const Tag    rname = "->"; Coerce(rname) += sid;
                    const Motif  motif = RegExp::Compile(rxp, & *design.pdb);
                    const Tag    rdata = sid;
                    add( new Rule(rname,motif,attr,rdata) );
                }

                template <typename RXP>
                void back(const RXP      &rxp,
                          const Attribute attr)
                {
                    const Tag    rname = "<--";
                    const Motif  motif = RegExp::Compile(rxp, & *design.pdb);
                    add( new Rule(rname,motif,attr,design.nil.tag) );
                }



                Status run(Source &         source,
                           AutoPtr<Unit>  & hUnit,
                           const String * & hData);


                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                const Tag    name; //!< uuid
            private:
                class Code;
                Code * const code; //!< inner code

                Y_Disable_Copy_And_Assign(Scanner); //!< discarding
                static Code *Impl(const Tag &);     //!< create code from tag
                void add(Rule * const rule);        //!< record new rule

            public:
                Design          design; //!< helper for rules
                const EOFPolicy policy; //!< EOF policy
            };


        }
    }

}

#endif

