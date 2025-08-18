
//! \file

#ifndef Y_Jive_Syntax_Aggregate_Included
#define Y_Jive_Syntax_Aggregate_Included 1

#include "y/jive/syntax/rule/logical.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Syntax
        {

            enum Property
            {
                Normal,
                Acting,
                Grouping
            };

            //__________________________________________________________________
            //
            //
            //
            //! Aggregate of existing rules
            //
            //
            //__________________________________________________________________
            class Aggregate : public Logical
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                static const uint32_t UUID = Y_FOURCC('A', 'G', 'G', '_'); //!< alias

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup \param rid rule name
                template <typename RID> inline
                explicit Aggregate(const RID &rid, const Property pty) :
                Logical(rid,UUID),
                ppty(pty)
                {
                }

                //! cleanup
                virtual ~Aggregate() noexcept;

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
                const Property ppty;

            private:
                Y_Disable_Copy_And_Assign(Aggregate); //!< discarding
            };

            template <Property PTY>
            class AggregateIs : public Aggregate
            {
            public:
                template <typename RID> inline
                explicit AggregateIs(const RID &rid) : Aggregate(rid,PTY) {}
                inline virtual ~AggregateIs() noexcept {}
            private:
                Y_Disable_Copy_And_Assign(AggregateIs);
            };



        }

    }

}

#endif

