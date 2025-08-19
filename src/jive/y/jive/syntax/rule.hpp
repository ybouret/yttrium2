
//! \file

#ifndef Y_Jive_Syntax_Rule_Included
#define Y_Jive_Syntax_Rule_Included 1

#include "y/jive/syntax/node.hpp"

namespace Yttrium
{
    namespace Jive
    {

        class Parser;

        namespace Syntax
        {


            
            //! helper for Rule::accepts arguments
#define Y_Jive_XRule_Args Node * &, Lexer &, Source &, size_t

            //__________________________________________________________________
            //
            //
            //
            //! Rule interface
            //
            //
            //__________________________________________________________________
            class Rule : public Category_
            {
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
            public:
                static bool Verbose; //!< verbosity, mostly to debug

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
            protected:
                //! setup
                /**
                 \param r rule name
                 \param t rule category
                 \param u rule class identifier
                 */
                template <typename RID> inline
                explicit Rule(const RID     &r,
                              const Category t,
                              const uint32_t u) :
                Category_(t),
                name(r),
                uuid(u),
                next(0),
                prev(0),
                pptr(0)
                {
                }
                
            public:
                virtual ~Rule() noexcept; //!< cleanup

                //______________________________________________________________
                //
                //
                // Interface
                //
                //______________________________________________________________

                //! \return true if this rule accepted lexer/source
                virtual bool           accepts(Y_Jive_XRule_Args) const = 0;
                virtual OutputStream & vizDecl(OutputStream &)    const = 0; //!< name and type    \return output stream
                virtual OutputStream & vizPost(OutputStream &)    const = 0; //!< possible linking \return output stream


                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                const Tag       name; //!< name
                const uint32_t  uuid; //!< uuid
                Rule *          next; //!< for list
                Rule *          prev; //!< for list
                Parser * const pptr; //!< owning grammar

            private:
                Y_Disable_Copy_And_Assign(Rule); //!< discarding
            };

            //! helper for verbosity
#define Y_Jive_XRule(MSG) do { if(Syntax::Rule::Verbose) { Core::Indent(std::cerr,depth<<1,'.') << MSG << std::endl; } } while(false)
            
        }
    }


}

#endif

