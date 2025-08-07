
#include "y/jive/lexical/scanner.hpp"
#include "y/pointer/auto.hpp"
#include "y/system/exception.hpp"
#include "y/object/school-of.hpp"
#include "y/type/destroy.hpp"
#include "y/ascii/printable.hpp"

namespace Yttrium
{
    namespace Jive
    {

        namespace Lexical
        {

            bool Scanner::Verbose = false;

#define Y_PRINT(MSG) \
do { if(Scanner::Verbose) { std::cerr << "<" << name << "> " << MSG << std::endl; } } while(false)

            namespace
            {
                class RNode : public Object
                {
                public:
                    explicit RNode(const Rule * const r) noexcept : rule(r), next(0), prev(0)
                    {
                    }

                    virtual ~RNode() noexcept
                    {
                    }

                    const Rule * const rule;
                    RNode *            next;
                    RNode *            prev;

                private:
                    Y_Disable_Copy_And_Assign(RNode);
                };

                typedef Core::ListOf<RNode> RList;

            }


            class Scanner:: Code : public Object
            {
            public:
                inline explicit Code(const Tag &uid) :
                name(uid), rlist(256), rules()
                {
                    Y_PRINT(" scanner was created");
                    for(unsigned i=0;i<256;++i) new (rlist.entry+i) RList();
                }

                inline virtual ~Code() noexcept
                {
                    for(unsigned i=0;i<256;++i)
                    {
                        RList &list = rlist.entry[i];
                        while(list.size) delete list.popTail();
                    }
                }

                inline void add(Rule * const rule)
                {


                    // ensure no duplicate
                    {
                        AutoPtr<Rule> guard(rule);
                        const String &id = *rule->name;
                        for(const Rule *r=rules.head;r;r=r->next)
                        {
                            if( *r->name == id ) throw Specific::Exception( name->c_str(), "mutliple rule '%s'", id.c_str());
                        }
                        guard.dismiss();
                    }

                    // append to global list
                    Coerce(rules).pushTail(rule);

                    // append to local list
                    const FirstChars fc = rule->motif->firstChars();
                    Y_PRINT("[+] |" << rule->humanReadableAttr()
                            << ":" << rule->humanReadableDeed()
                            << "|  '" << rule->name << "'"
                            << " @" << fc);
                    try {
                        for(unsigned i=0;i<256;++i)
                        {
                            if(!fc.getbit(i)) continue;
                            rlist.entry[i].pushTail( new RNode(rule) );
                        }
                    }
                    catch(...)
                    {
                        purge(rule,fc);
                        delete Coerce(rules).popTail();
                        throw;
                    }
                }


                const Tag               name;
                Memory::SchoolOf<RList> rlist;
                Rule::List              rules;

            private:
                Y_Disable_Copy_And_Assign(Code);
                inline void purge(const Rule * const rule, const FirstChars &fc) noexcept
                {
                    for(unsigned i=0;i<256;++i)
                    {
                        if( !fc.getbit(i) ) continue;
                        
                        RList &list = rlist.entry[i];
                        for(RNode *node=list.head;node;node=node->next)
                        {
                            if( rule == node->rule )
                            {
                                delete list.pop(node);
                                break;
                            }
                        }
                    }
                }


            };

            Scanner:: ~Scanner() noexcept
            {
                assert(code);
                Destroy(code);
            }

            Scanner::Code * Scanner:: New(const Tag &tag)
            {
                return new Code(tag);
            }

            const String & Scanner:: key() const noexcept
            {
                return *name;
            }

            const Rule & Scanner:: add(Rule *const rule)
            {
                assert(0!=rule);
                assert(0!=code);
                code->add(rule);
                return *rule;
            }

            



            Status Scanner:: run(Source &         source,
                                 AutoPtr<Unit> &  hUnit,
                                 const String * & hData)
            {
                assert(0==hData);
                assert(hUnit.isEmpty());

            PROBE:
                //______________________________________________________________
                //
                //
                // look for next char un source
                //
                //______________________________________________________________
                assert(0!=code);
                const Char * const ch  = source.peek();
                if(!ch)
                {
                    // deal with EOF
                    switch(policy)
                    {
                        case AcceptEOF: Y_PRINT("EOF"); return FoundEOF;
                        case RejectEOF: throw Specific::Exception(name->c_str(),"%s unexpected EOF",source.context().str().c_str());
                    }
                }
                const Context      ctx = *ch; // save context

                const Rule *bestRule = 0;
                Token       bestToken;
                {
                    //_________________________________________________________
                    //
                    //
                    // find bestRule within recorded rule
                    //
                    //__________________________________________________________
                    const uint8_t c = **ch;                 // char code
                    const RList  &L = code->rlist.entry[c]; // possible rule(s)
                    //std::cerr << "L[" << ASCII::Printable::Char[c] << "]=" << L.size << std::endl;
                    const RNode * node  = L.head;
                    for(;node;node=node->next)
                    {
                        assert(node->rule);
                        const Rule * const rule = node->rule;
                        if(rule->motif->accepts(bestToken,source))
                        {
                            bestRule = rule;
                            break;
                        }
                    }

                    if(!bestRule)
                    {
                        // syntax error
                        const char * const which = ASCII::Printable::Char[c];
                        Y_PRINT("no rule matching '" << which << "'");
                        const String where = ch->str();
                        throw Specific::Exception( name->c_str(), "%s unexpected '%s'", where.c_str(),which);
                    }

                    Y_PRINT("selected '" << bestRule->name << "'='" << bestToken);

                    //__________________________________________________________
                    //
                    //
                    // try to find better rule
                    //
                    //__________________________________________________________
                    source.stash(bestToken);

                    for(node=node->next;node;node=node->next)
                    {
                        assert(node->rule);
                        const Rule * const rule  = node->rule;
                        Token              token;
                        if(!rule->motif->accepts(token,source))
                        {
                            continue;
                        }
                        source.stash(token);

                        if(token.size>bestToken.size)
                        {
                            bestRule = rule; std::cerr << "new Rule=" << rule->name << std::endl;
                            bestToken.swapListFor(token);
                            Y_PRINT("improved '" << bestRule->name << "'='" << bestToken);
                        }
                        else
                        {
                            Y_PRINT("loosing  '" << rule->name << "'='" << token);

                        }
                    }
                }

                //______________________________________________________________
                //
                //
                // update source
                //
                //______________________________________________________________
                source.sweep(bestToken.size);

                Y_PRINT( "=> |" << bestRule->humanReadableAttr() << ":" << bestRule->humanReadableDeed() << "| @ '" << bestToken << "'");
                switch(bestRule->attr)
                {
                    case Regular: break;
                    case NewLine: source.endl(); break;
                }

                //______________________________________________________________
                //
                //
                // take lexical action
                //
                //______________________________________________________________
                switch(bestRule->deed)
                {
                    case Drop:
                        goto PROBE;

                    case Back:
                        assert(0 == bestRule->data->length() );
                        onBack(bestToken);
                        return CtrlBack;

                    case Call:
                        assert( 0 < bestRule->data->length() );
                        hUnit = new Unit(bestRule->name,ctx,bestToken);
                        hData = & *bestRule->data;
                        return CtrlCall;
                        
                    case Emit:
                        hUnit = new Unit(bestRule->name,ctx,bestToken);
                        return EmitUnit;


                }

                throw Specific::Exception(name->c_str(),"*** corrupted");

            }

        }


    }

}

