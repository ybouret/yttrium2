//! \file

#ifndef Y_Jive_Syntax_AtLeast_Included
#define Y_Jive_Syntax_AtLeast_Included 1

#include "y/jive/syntax/rule/wildcard.hpp"

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
            //! AtLeast rule
            //
            //
            //__________________________________________________________________
            class AtLeast : public Wildcard
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                static const uint32_t UUID = Y_FOURCC('R', 'E', 'P', '_'); //!< alias

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup \param rid rule name \param nmin minCount \param f persistent rule
                template <typename RID> inline
                explicit AtLeast(const RID &rid, const size_t nmin, const Rule &f) :
                Wildcard(rid,UUID,f),
                minCount(nmin)
                {
                }

                //! cleanup
                virtual ~AtLeast() noexcept;

                //______________________________________________________________
                //
                //
                // Interface
                //
                //______________________________________________________________
                virtual bool           accepts(Y_Jive_XRule_Args) const;
                virtual OutputStream & vizDecl(OutputStream &)    const;

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                const size_t minCount; //!< minimal valid count

            private:
                Y_Disable_Copy_And_Assign(AtLeast); //!< discarding
            };


            //__________________________________________________________________
            //
            //
            //
            //! AtLeast>=0
            //
            //
            //__________________________________________________________________
            class ZeroOrMore : public AtLeast
            {
            public:
                //! setup \param r rule name \param f foreign rule
                template <typename RID> inline
                explicit ZeroOrMore(const RID &r, const Rule &f) : AtLeast(r,0,f) {}
                virtual ~ZeroOrMore() noexcept;        //!< cleanup
            private:
                Y_Disable_Copy_And_Assign(ZeroOrMore); //!< discarding
            };

            //__________________________________________________________________
            //
            //
            //
            //! AtLeast>=1
            //
            //
            //__________________________________________________________________
            class OneOrMore : public AtLeast
            {
            public:
                //! setup \param r rule name \param f foreign rule
                template <typename RID> inline
                explicit OneOrMore(const RID &r, const Rule &f) : AtLeast(r,1,f) {}
                virtual ~OneOrMore() noexcept;        //!< cleanup
            private:
                Y_Disable_Copy_And_Assign(OneOrMore); //!< discarding
            };
        }

    }

}

#endif

