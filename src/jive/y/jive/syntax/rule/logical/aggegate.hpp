
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

            //__________________________________________________________________
            //
            //
            //! Aggregate property
            //
            //__________________________________________________________________
            enum Property
            {
                Standard, //!< named aggregate
                ActingAs, //!< named aggregate but if size<=1
                Grouping, //!< grouping only
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

                //! setup \param rid rule name \param pty property
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
                const Property ppty; //!< property

            private:
                Y_Disable_Copy_And_Assign(Aggregate); //!< discarding
            };

            //__________________________________________________________________
            //
            //
            //! Specialized Aggregate
            //
            //__________________________________________________________________
            template <Property PTY>
            class AggregateIs : public Aggregate
            {
            public:
                //! setup \param rid name
                template <typename RID> inline
                explicit AggregateIs(const RID &rid) : Aggregate(rid,PTY) {}
                inline virtual ~AggregateIs() noexcept {} //!< cleanup
            private:
                Y_Disable_Copy_And_Assign(AggregateIs); //!< discarding
            };



        }

    }

}

#endif

