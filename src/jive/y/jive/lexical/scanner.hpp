
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
                typedef Keyed< String,ArcPtr<Scanner> > Pointer; //!< alias
                static  bool                            Verbose; //!< default to false

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup
                /**
                 \param sid scanner id
                 \param com for design
                 \param eof for policy
                 */
                template <typename SID> inline
                explicit Scanner(const uint32_t  uid,
                                 const SID    &  sid,
                                 const Design &  com,
                                 const EOFPolicy eof) :
                CountedObject(),
                uuid(uid),
                name(sid),
                code( New(name) ),
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
                virtual void onCall(Token &enter) = 0; //!< what to do on call \param enter trigger in
                virtual void onBack(Token &leave) = 0; //!< what to do on back \param leave trigger out
                virtual void onSent(Token &token) = 0; //!< what to on on sent \param token sent by run

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________

                void forbidden(const char * const method, const Token &) const;


                const String & key() const noexcept; //!< \return *name

                //! declare a new standard rule
                /**
                 \param rid  rule name
                 \param rxp  rule regular expression
                 \param attr rule attribute
                 \param ppty requested property
                 \return added rule
                 */
                template <typename RID, typename RXP>
                const Rule & decl(const RID &              rid,
                                  const RXP &              rxp,
                                  const Attribute          attr,
                                  const Property           ppty)
                {
                    const Tag    rname = rid;
                    const Motif  motif = RegExp::Compile(rxp, & *design.pdb );
                    return add( new Rule(rname,motif,attr,ppty,design.nil.tag) );
                }

                //! declare a new send rule, Regular
                /**
                 \param rid rule name
                 \param rxp rule regular expression
                 \return added rule
                 */
                template <typename RID, typename RXP>
                const Rule & send(const RID &              rid,
                                  const RXP &              rxp)
                {
                    const Tag    rname = rid;
                    const Motif  motif = RegExp::Compile(rxp, & *design.pdb );
                    return add( new Rule(rname,motif,Regular,SendToken,design.nil.tag) );
                }

                //! declare a new error rule, Regular
                /**
                 \param rid rule name
                 \param rxp rule regular expression
                 \return added rule
                 */
                template <typename RID, typename RXP>
                const Rule & halt(const RID &              rid,
                                  const RXP &              rxp)
                {
                    const Tag    rname = rid;
                    const Motif  motif = RegExp::Compile(rxp, & *design.pdb );
                    return add( new Rule(rname,motif,Regular,BadSyntax,design.nil.tag) );
                }



                //! declare a call rule
                /**
                 \param sid scanner to call
                 \param rxp rule regular expression
                 \param attr rule attribute, should be regular
                 \return added rule
                 */
                template <typename SID, typename RXP>
                const Rule &  call(const SID &     sid,
                                   const RXP &     rxp,
                                   const Attribute attr = Regular)
                {
                    const Tag    rname = "@"; Coerce(rname) += sid;
                    const Motif  motif = RegExp::Compile(rxp, & *design.pdb);
                    const Tag    rdata = sid;
                    return add( new Rule(rname,motif,attr,rdata) );
                }

                //! declare a back rule
                /**
                 \param rxp rule regular expression
                 \param attr rule attribute
                 \return added rule
                 */
                template <typename RXP>
                const Rule &  back(const RXP      &rxp,
                                   const Attribute attr)
                {
                    const Tag    rname = "<-";
                    const Motif  motif = RegExp::Compile(rxp, & *design.pdb);
                    return add( new Rule(rname,motif,attr,design.nil.tag) );
                }

                //! emit regular
                /**
                 \param rid rule name
                 \param rxp rule regular expression
                 \return added regular, Emit rule
                 */
                template <typename RID, typename RXP>
                const Rule & emit(const RID & rid,
                                  const RXP & rxp)
                {
                    return decl(rid,rxp,Regular,SpawnUnit);
                }

                //! drop regular
                /**
                 \param rid rule name
                 \param rxp rule regular expression
                 \return added regular, Drop rule
                */
                template <typename RID, typename RXP>
                const Rule & drop(const RID & rid,
                                  const RXP & rxp)
                {
                    return decl(rid,rxp,Regular,DropToken);
                }

                //! flexible endl
                /**
                 \param rid endl name
                 \param rxp endl regular expression
                 \param rise optional Emit
                 \return added endl rule
                 */
                template <typename RID, typename RXP>
                const Rule & endl(const RID & rid,
                                  const RXP & rxp,
                                  const bool  rise = false)
                {
                    return decl(rid,rxp,NewLine,rise ? SpawnUnit : DropToken);
                }

                //! look up algorithm
                /**
                 \param source current source
                 \param hUnit store created unit if needed
                 \param hData scanner name for Call
                 \return detected status with matching parameters
                 */
                Status run(Source &         source,
                           AutoPtr<Unit>  & hUnit,
                           const String * & hData);


                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                const uint32_t uuid; //!< class identifier
                const Tag      name; //!< identifier

            private:
                class Code;
                Code * const code; //!< inner code

                Y_Disable_Copy_And_Assign(Scanner); //!< discarding
                static Code * New(const Tag &);      //!< \return ne code from tag
                const Rule &  add(Rule * const);     //!< \return recorded new rule

            public:
                Design          design; //!< helper for rules
                const EOFPolicy policy; //!< EOF policy
            };


        }
    }

}

#endif

